# Every SL directory has a symbolic link to config/bazel to access the config files as local path.
# While not pretty, this allows BUILD files to be independt of the SL_ROOT workspace path, and only
# SL.bzl needs to be adjusted
load(":bazel/SL.bzl", "SL_ROOT", "SL_ROOT_WS", "SL_VISIBILITY")

package(default_visibility = SL_VISIBILITY)

licenses(["notice"])

exports_files(["LICENSE"])

# the name of this robot: various rules use the NAME such that BUILD files are easy to adapt to another robot
NAME = "panda"

# the root directory of this robot user implementation
ROBOT_DIR = "pandaUser/"

# the configs are to accommodate the SL cmake out-of-source naming of build directories on
# different operating systems. The definition of MACHTYPE is passed as --define in bazel build command.
# See bazel/bazelrc directory. By default, SL looks for the binaries in this <NAME>/MACHTYPE local directory
# for execution. Of course, this could be changed and the binaries could be in any suitable "bin" directory.
# See genrules below if you want to modify.
config_setting(
    name = "x86_64mac",
    define_values = {"MACHTYPE": "x86_64mac"},
)

config_setting(
    name = "x86_64",
    define_values = {"MACHTYPE": "x86_64"},
)

# SL builds several binaries, which are started by the x<NAME> binary
cc_binary(
    name = "x" + NAME,
    srcs = [
        SL_ROOT + NAME + ":main_srcs",
    ],
    includes = [
        "include",
    ],
    deps = [
        SL_ROOT + NAME + ":" + NAME,
        SL_ROOT + "SL:SLcommon",
        SL_ROOT + "utilities:utility",
        "//third_party/Xorg:X11headers",	
        # "//third_party/Xorg:libX11",
        # "//third_party/freeglut:headers",
        # "//third_party/freeglut:native",
        # "//third_party/glu:native",
    ],
)

# xtask is the key process to run tasks created by a user
cc_binary(
    name = "xtask",
    srcs = [
        "src/gravcomp_task.c",
        "src/initUserTasks.c",
        "src/sample_task.c",
        "src/sample_task_cpp.cpp",
    ],
    includes = [
        "include",
    ],
    deps = [
        SL_ROOT + "SL:SLcommon",
        SL_ROOT + "SL:SLtask",
        SL_ROOT + NAME + ":" + NAME,
        SL_ROOT + NAME + ":" + NAME + "_task",
        SL_ROOT + "utilities:utility",
    ],
)

# xmotor is the process that commnicates with the robot (or simulator)
cc_binary(
    name = "xmotor",
    srcs = [
        SL_ROOT + "panda:motor_srcs",
    ],
    includes = [
        "include",
    ],
    deps = [
        SL_ROOT + "SL:SLcommon",
        SL_ROOT + "SL:SLmotor",
        SL_ROOT + NAME + ":" + NAME,
        SL_ROOT + "utilities:utility",
    ],
)

# xopengl is the graphics/visualization process
cc_binary(
    name = "xopengl",
    srcs = [
        "src/initUserGraphics.c",
    ],
    includes = [
        "include",
    ],
    deps = [
        SL_ROOT + "SL:SLcommon",
        SL_ROOT + "SL:SLopenGL",
        SL_ROOT + NAME + ":" + NAME,
        SL_ROOT + NAME + ":" + NAME + "_openGL",
        SL_ROOT + "utilities:utility",
        # "//third_party/Xorg:libX11",
        # "//third_party/freeglut:headers",
        # "//third_party/freeglut:native",
        # "//third_party/glu:native",
    ],
)

# xsimulation is the process of the physical simulator
cc_binary(
    name = "xsimulation",
    srcs = [
        "src/initUserSimulation.c",
    ],
    includes = [
        "include",
    ],
    deps = [
        SL_ROOT + "SL:SLcommon",
        SL_ROOT + "SL:SLsimulation",
        SL_ROOT + NAME + ":" + NAME,
        SL_ROOT + NAME + ":" + NAME + "_simulation",
        SL_ROOT + "utilities:utility",
    ],
)

# xpest is an independent binary to do rigid-body-dynamics parameter identification
cc_binary(
    name = "xpest",
    srcs = [
        SL_ROOT + "SL:parm_est_srcs",
    ],
    includes = [
        "include",
    ],
    deps = [
        SL_ROOT + NAME + ":" + NAME,
        SL_ROOT + "SL:SLcommon",
        SL_ROOT + "utilities:utility",
    ],
)

# the following genrules just copy binaries to the MACHTYPE directory. To avoid errors in genrule, the official output $@ needs
# to be written (by touch). Note that it is not the BAZEL way to modify a source directory by copying
# executable files into it. This could be changed, but it is the easiest compatibility with the CMAKE build.

CMD_X86_64MAC_1 = "mkdir -p " + ROBOT_DIR + "x86_64mac && touch $@ && mv -f $(BINDIR)/" + ROBOT_DIR

CMD_X86_64MAC_2 = " " + ROBOT_DIR + "x86_64mac/"

CMD_X86_64_1 = "mkdir -p " + ROBOT_DIR + "x86_64 && touch $@ && mv -f $(BINDIR)/" + ROBOT_DIR

CMD_X86_64_2 = " " + ROBOT_DIR + "x86_64/"

genrule(
    name = "install_xtask",
    srcs = [":xtask"],
    outs = [ROBOT_DIR + "x86_64/xtask"],
    cmd = select({
        ":x86_64mac": CMD_X86_64MAC_1 + "xtask" + CMD_X86_64MAC_2,
        ":x86_64": CMD_X86_64_1 + "xtask" + CMD_X86_64_2,
        "//conditions:default": CMD_X86_64_1 + "xtask" + CMD_X86_64_2,
    }),
    local = 1,
)

genrule(
    name = "install_xmotor",
    srcs = [":xmotor"],
    outs = [ROBOT_DIR + "x86_64/xmotor"],
    cmd = select({
        ":x86_64mac": CMD_X86_64MAC_1 + "xmotor" + CMD_X86_64MAC_2,
        ":x86_64": CMD_X86_64_1 + "xmotor" + CMD_X86_64_2,
        "//conditions:default": CMD_X86_64_1 + "xmotor" + CMD_X86_64_2,
    }),
    local = 1,
)

genrule(
    name = "install_xsimulation",
    srcs = [":xsimulation"],
    outs = [ROBOT_DIR + "x86_64/xsimulation"],
    cmd = select({
        ":x86_64mac": CMD_X86_64MAC_1 + "xsimulation" + CMD_X86_64MAC_2,
        ":x86_64": CMD_X86_64_1 + "xsimulation" + CMD_X86_64_2,
        "//conditions:default": CMD_X86_64_1 + "xsimulation" + CMD_X86_64_2,
    }),
    local = 1,
)

genrule(
    name = "install_xopengl",
    srcs = [":xopengl"],
    outs = [ROBOT_DIR + "x86_64/xopengl"],
    cmd = select({
        ":x86_64mac": CMD_X86_64MAC_1 + "xopengl" + CMD_X86_64MAC_2,
        ":x86_64": CMD_X86_64_1 + "xopengl" + CMD_X86_64_2,
        "//conditions:default": CMD_X86_64_1 + "xtask" + CMD_X86_64_2,
    }),
    local = 1,
)

genrule(
    name = "install_xpanda",
    srcs = [":xpanda"],
    outs = [ROBOT_DIR + "x86_64/xpanda"],
    cmd = select({
        ":x86_64mac": CMD_X86_64MAC_1 + "xpanda" + CMD_X86_64MAC_2,
        ":x86_64": CMD_X86_64_1 + "xpanda" + CMD_X86_64_2,
        "//conditions:default": CMD_X86_64_1 + "xpanda" + CMD_X86_64_2,
    }),
    local = 1,
)

genrule(
    name = "install_xpest",
    srcs = [":xpest"],
    outs = [ROBOT_DIR + "x86_64/xpest"],
    cmd = select({
        ":x86_64mac": CMD_X86_64MAC_1 + "xpest" + CMD_X86_64MAC_2,
        ":x86_64": CMD_X86_64_1 + "xpest" + CMD_X86_64_2,
        "//conditions:default": CMD_X86_64_1 + "xpest" + CMD_X86_64_2,
    }),
    local = 1,
)
