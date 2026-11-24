# AcetyleneC plugins

AcetyleneC loads plugins from `plugins/<name>/` at start-up, the way VS Code loads extensions:
every plugin is a directory with a `plugin.json` manifest, one or more DLLs and any resources it
needs. A plugin can add commands, menu items, diagnostics, completion providers, file viewers and
event handlers. It cannot remove or replace built-in IDE behaviour.

## Manifest

```json
{
  "id": "acetylene.jsonlint",
  "name": "JSON Linter",
  "version": "1.0.0",
  "api": 1,
  "entry": "jsonlint.dll",
  "description": "Validates .json files and reports errors in the output pane"
}
```

`entry` is the DLL loaded from the plugin directory. `api` must match `AC_PLUGIN_API_VERSION`
(currently 1). Unknown keys are ignored, so a plugin may carry its own settings here.

The loader scans `<exe dir>/../../plugins/*`, reads each manifest and calls the DLL's exported
`ac_plugin_init`. Load results, including failures with their Win32 error codes, are appended to
`build/bin/acetylene-ide.log`.

## Required exports

```c
__declspec(dllexport) int  ac_plugin_api(void);                 /* return AC_PLUGIN_API_VERSION */
__declspec(dllexport) int  ac_plugin_init(AcPlugin *self);      /* return 1 on success */
__declspec(dllexport) void ac_plugin_shutdown(void);            /* optional */
```

`AcPlugin` carries the host vtable and the plugin's own directory:

```c
typedef struct {
    const AcHostApi *host;
    const char *plugin_id;
    const char *plugin_dir;
} AcPlugin;
```

`host->plugin_dir` is the place to look for the plugin's own resources. The whole ABI is in
[`include/ac_plugin.h`](../include/ac_plugin.h); there is no C++ requirement, everything is a plain
C function pointer table, so plugins can be written with the bundled TCC-compatible C or any Win32
toolchain.

## Host API

| Group | Functions |
|---|---|
| Buffer | `doc_text`, `doc_length`, `cursor_pos`, `insert_text`, `replace_range`, `set_cursor` |
| Position | `doc_path`, `doc_line_of`, `line_start`, `line_end` |
| UI | `status`, `output`, `invalidate`, `log` |
| Registration | `register_command`, `menu_add`, `add_diagnostic`, `clear_diagnostics`, `register_completion`, `register_viewer`, `subscribe` |
| IDE actions | `root_dir`, `plugin_dir`, `run_command`, `open_file` |

`menu_add("Build", label, cmd_id)` appends to an existing menu (`File`, `Edit`, `Build`, `View`,
`Help`, `Plugins`); the `Plugins` menu additionally lists every registered command automatically.

`run_command` accepts the IDE's own command identifiers: `build`, `rebuild`, `package`, `sign`,
`run`. `open_file` opens a source file, or loads a `.acproj` project when the path ends with that
extension.

Diagnostics are drawn above the build log in the output pane with the plugin's severity
(`AC_SEV_ERROR`, `AC_SEV_WARNING`, `AC_SEV_INFO`); line and column are zero-based and displayed
one-based.

Completion providers receive the typed prefix and write one candidate per line into the output
buffer. Pressing `Ctrl+Space` or typing two or more identifier characters opens the popup; `Up`/
`Down` select, `Enter`, `Tab` or `Space` accept, `Esc` closes.

Viewers are registered per extension and draw into the editor rect with a plain `HDC`; the plugin
owns the GDI+ or GDI calls. Returning 0 leaves the pane empty instead of falling back to text.

## Events

`subscribe(event, fn, user)` registers a handler for:

| Event | Fired when |
|---|---|
| `AC_EV_DOC_OPEN` | a document is activated or opened |
| `AC_EV_DOC_SAVE` | a document is written to disk |
| `AC_EV_DOC_CHANGED` | the buffer changed (typing, paste, undo, plugin edits) |
| `AC_EV_BUILD_OK` | the build pipeline produced an E32 |
| `AC_EV_BUILD_FAIL` | the pipeline failed |

Handlers run on the IDE thread whenever the IDE fires the event.

## Building the examples

```sh
sh build/build-plugins.sh
```

This compiles every bundled plugin into its own directory with the same 32-bit MinGW used for the
rest of the repo (`imageviewer` links `gdiplus`, `mcp` links `ws2_32`). Rebuild the IDE with
`sh build/build-tools.sh`, then start `build/bin/AcetyleneC.exe`; the Plugins menu shows what was
loaded.

The test suite validates the plugins without the GUI through `build/bin/plugin-host.exe`, a stub
host that implements the whole vtable in memory:

```sh
build/bin/plugin-host.exe plugins/jsonlint probe
```

It loads the DLL, calls the manifest entry, exercises the JSON linter on valid and broken input,
checks the completion provider and prints the registered commands, menus, viewers and subscribers.
`plugin-host.exe plugins/mcp serve 10` keeps the message loop alive so an MCP client can connect.

## Bundled plugins

| Directory | What it does |
|---|---|
| `plugins/autocomplete` | Suggests Symbian/C identifiers from a keyword table plus every word already in the buffer. `Edit > Autocomplete: self test`. |
| `plugins/imageviewer` | Draws `.png`, `.jpg`, `.jpeg`, `.bmp`, `.gif` inside the editor pane, scaled to fit, with GDI+ bicubic sampling. |
| `plugins/jsonlint` | Strict JSON parser; flags the first syntax error with its line and column on open, save and every edit. `Build > JSON: lint current file`. |
| `plugins/mcp` | Local Model Context Protocol server over TCP. `Plugins > MCP: start/stop server`, `Plugins > MCP: show server status`. |

## MCP server

The MCP plugin speaks JSON-RPC 2.0 over a loopback TCP socket, one message per line (or
`Content-Length` framing, both are accepted). It listens on `127.0.0.1` and picks its port in this
order:

1. `ACETYLENE_MCP_PORT` environment variable,
2. a `mcp.port` file inside `plugins/mcp/`,
3. 8765.

Tools:

| Tool | Arguments | Result |
|---|---|---|
| `ide_get_text` | `start`, `end` (bytes, optional) | Buffer contents |
| `ide_insert_text` | `text` | Inserts at the caret, errors when no document is open |
| `ide_get_path` | — | Path of the active document |
| `ide_build` | — | Queues the normal build pipeline |
| `ide_status` | `message` | Writes the status bar |
| `ide_open_file` | `path` | Opens a file or `.acproj` project |

`initialize`, `ping`, `tools/list`, `tools/call`, `resources/list` and `prompts/list` are
implemented; unknown methods return `-32601`, unknown tools return `isError: true`.

Host-side calls are marshalled onto the IDE thread through a message-only window, so the server
thread never touches the editor buffers directly.

Most MCP clients only speak stdio. `build/bin/acetylene-mcp-stdio.exe` bridges the two:

```json
{
  "mcpServers": {
    "acetylene": {
      "command": "F:\\NNPROJECT_WORK\\symbian-sdk\\build\\bin\\acetylene-mcp-stdio.exe",
      "args": ["8765"]
    }
  }
}
```

The bridge connects lazily, forwards each stdin line to the IDE and writes the reply to stdout.
