import os
Import("env")

# https://docs.platformio.org/en/latest/projectconf/advanced_scripting.html
# https://docs.platformio.org/en/latest/projectconf/section_env_build.html#projectconf-dynamic-build-flags

def after_build(source, target, env): 
    """ Run objdump on the target elf file and save the output in the top dir.
    """
    objdump=env.subst("${OBJCOPY}").replace("objcopy","objdump")
    src_elf=env.subst("${BUILD_DIR}/${PROGNAME}.elf")
    # --disassembler-options=no-aliases,numeric 
    cmd=" ".join([
        objdump, "-SC","--file-start-context", "-w",
        src_elf,">","${PROGNAME}.disasm"]) # 
    env.Execute(cmd)

env.AddCustomTarget(
    "disasm",
    "${BUILD_DIR}/${PROGNAME}.elf",
    after_build,
    title="Disasm 2",
    description="Generate a disassembly file on demand",
    always_build=True
)

# The environment can be inspected:
#print(env.Dump())
#print(projenv.Dump())
