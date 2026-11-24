#include "../../include/ac_plugin.h"
#include <windows.h>
#include <gdiplus.h>
#include <string.h>
#include <stdio.h>

static const AcHostApi *H;
static ULONG_PTR g_token;

static int paint(void *hdc, int x, int y, int w, int h, const char *path, void *user)
{
    WCHAR wide[MAX_PATH * 2];
    GpBitmap *bmp = NULL;
    GpGraphics *g = NULL;
    UINT iw = 0, ih = 0;
    (void)user;
    if (!hdc || !path || !path[0])
        return 0;
    if (!MultiByteToWideChar(CP_ACP, 0, path, -1, wide, MAX_PATH * 2))
        return 0;
    if (GdipCreateBitmapFromFile(wide, &bmp) != Ok)
        return 0;
    GdipGetImageWidth((GpImage *)bmp, &iw);
    GdipGetImageHeight((GpImage *)bmp, &ih);
    if (GdipCreateFromHDC((HDC)hdc, &g) == Ok) {
        int dw = (int)iw;
        int dh = (int)ih;
        GdipSetInterpolationMode(g, InterpolationModeHighQualityBicubic);
        if (dw > w || dh > h) {
            double sx = (double)w / (double)dw;
            double sy = (double)h / (double)dh;
            double s = sx < sy ? sx : sy;
            dw = (int)(dw * s);
            dh = (int)(dh * s);
        }
        if (dw < 1)
            dw = 1;
        if (dh < 1)
            dh = 1;
        GdipDrawImageRectI(g, (GpImage *)bmp, x + (w - dw) / 2, y + (h - dh) / 2, dw, dh);
        GdipDeleteGraphics(g);
    }
    GdipDisposeImage((GpImage *)bmp);
    return 1;
}

static void cmd_info(void)
{
    const char *p = H->doc_path();
    H->status(p && p[0] ? "image viewer: active file is shown as an image" : "image viewer: no file open");
}

__declspec(dllexport) int ac_plugin_api(void)
{
    return AC_PLUGIN_API_VERSION;
}

__declspec(dllexport) int ac_plugin_init(AcPlugin *self)
{
    GdiplusStartupInput in;
    H = self->host;
    memset(&in, 0, sizeof(in));
    in.GdiplusVersion = 1;
    if (GdiplusStartup(&g_token, &in, NULL) != Ok)
        return 0;
    H->register_viewer(".png", paint, NULL);
    H->register_viewer(".jpg", paint, NULL);
    H->register_viewer(".jpeg", paint, NULL);
    H->register_viewer(".bmp", paint, NULL);
    H->register_viewer(".gif", paint, NULL);
    H->register_command("imageviewer.info", "Image: about current file", cmd_info);
    H->menu_add("View", "Image: about current file", "imageviewer.info");
    H->log("image viewer ready");
    return 1;
}

__declspec(dllexport) void ac_plugin_shutdown(void)
{
    if (g_token)
        GdiplusShutdown(g_token);
}
