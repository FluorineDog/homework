from ctypes import *
handle = cdll.LoadLibrary("build/libmd5.so")
message = create_string_buffer(120)
print(handle.md5(message, 2**54))
print(repr(message.raw))
