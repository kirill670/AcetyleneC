import json
import socket
import sys
import time

port = int(sys.argv[1]) if len(sys.argv) > 1 else 8765
host = "127.0.0.1"

sock = None
for _ in range(40):
    try:
        sock = socket.create_connection((host, port), 1)
        break
    except OSError:
        time.sleep(0.15)

if sock is None:
    print("probe: cannot connect to %s:%d" % (host, port))
    sys.exit(1)

sock.settimeout(8)


def call(obj):
    sock.sendall((json.dumps(obj) + "\n").encode())
    buf = b""
    while not buf.endswith(b"\n"):
        chunk = sock.recv(65536)
        if not chunk:
            raise SystemExit("probe: connection closed")
        buf += chunk
    return json.loads(buf.decode())


def tool(name, **args):
    r = call({"jsonrpc": "2.0", "id": 1, "method": "tools/call",
              "params": {"name": name, "arguments": args}})
    return r["result"]["content"][0]["text"], r["result"].get("isError", False)


fail = []

init = call({"jsonrpc": "2.0", "id": 1, "method": "initialize",
             "params": {"protocolVersion": "2024-11-05", "capabilities": {},
                        "clientInfo": {"name": "acetylene-probe", "version": "1.0"}}})
if init["result"]["serverInfo"]["name"] != "acetylene-ide":
    fail.append("serverInfo.name")

names = [t["name"] for t in call({"jsonrpc": "2.0", "id": 2, "method": "tools/list"})["result"]["tools"]]
for want in ("ide_get_text", "ide_insert_text", "ide_get_path", "ide_build", "ide_status", "ide_open_file"):
    if want not in names:
        fail.append("tool " + want)

text = "int main(void)\n{\n    return 0;\n}\n"
res, err = tool("ide_insert_text", text=text)
if err:
    fail.append("insert: " + res)
got, _ = tool("ide_get_text")
if text not in got:
    fail.append("get_text round trip")

path, _ = tool("ide_get_path")
if not path.endswith(".c") and path != "":
    fail.append("get_path")

res, err = tool("ide_status", message="probe")
if err:
    fail.append("status")

res, err = tool("ide_build")
if "queued" not in res:
    fail.append("build")

res, err = tool("no_such_tool")
if not err:
    fail.append("unknown tool must fail")

err_code = call({"jsonrpc": "2.0", "id": 3, "method": "no/such"})["error"]["code"]
if err_code != -32601:
    fail.append("error code")

sock.close()

if fail:
    print("probe: FAIL " + ", ".join(fail))
    sys.exit(1)

print("probe: OK")
