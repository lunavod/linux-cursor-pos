#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <napi.h>

Napi::Object LinuxGetCursorPos(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::Object obj = Napi::Object::New(env);

	Display *display = XOpenDisplay(NULL);
    XEvent event;
    XQueryPointer(display, XDefaultRootWindow(display),
        &event.xbutton.root, &event.xbutton.window,
        &event.xbutton.x_root, &event.xbutton.y_root,
        &event.xbutton.x, &event.xbutton.y,
        &event.xbutton.state);

	auto x = Napi::Number::New(env, event.xbutton.x_root);
	auto y = Napi::Number::New(env, event.xbutton.y_root);

	obj.Set(Napi::String::New(env, "x"), x);
	obj.Set(Napi::String::New(env, "y"), y);

    XCloseDisplay(display);
    return obj;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
	return Napi::Function::New(env, LinuxGetCursorPos, "getCursorPos");
}

NODE_API_MODULE(addon, Init)