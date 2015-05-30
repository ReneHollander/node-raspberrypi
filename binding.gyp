{
  "targets": [
    {
      "target_name": "raspberrypi",
      "sources": [
        "src/videocore/ilclient/ilclient.c",
        "src/videocore/ilclient/ilcore.c",
        "src/videocore/omxhelper.c",
        "src/videocore/helper.c",
        "src/videocore/video.c",
        "src/videocore/image.c",
        "src/GPUInterface.cc",
        "src/raspberrypi.cc"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "/opt/vc/include/",
        "/opt/vc/include/IL",
        "/opt/vc/include/interface/vcos/pthreads",
        "/opt/vc/include/interface/vmcs_host/linux",
        "/opt/vc/include/interface/vchiq/"
      ],
      "cflags": [
        "-DSTANDALONE",
        "-D__STDC_CONSTANT_MACROS",
        "-D__STDC_LIMIT_MACROS",
        "-DTARGET_POSIX -D_LINUX",
        "-fPIC",
        "-DPIC",
        "-D_REENTRANT",
        "-D_LARGEFILE64_SOURCE",
        "-D_FILE_OFFSET_BITS=64",
        "-U_FORTIFY_SOURCE",
        "-Wall",
        "-g",
        "-DHAVE_LIBOPENMAX=2",
        "-DOMX",
        "-DOMX_SKIP64BIT",
        "-ftree-vectorize",
        "-pipe",
        "-DUSE_EXTERNAL_OMX",
        "-DHAVE_LIBBCM_HOST",
        "-DUSE_EXTERNAL_LIBBCM_HOST",
        "-DUSE_VCHIQ_ARM",
        "-Wno-psabi"
      ],
      "libraries": [
        "-L/opt/vc/lib/",
        "-lGLESv2",
        "-lEGL",
        "-lopenmaxil",
        "-lbcm_host",
        "-lvcos",
        "-lvcsm",
        "-lvchiq_arm",
        "-lpthread",
        "-lrt",
        "-lm"
      ]
    }
  ]
}
