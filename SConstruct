# Target Compilation Mode #
base_compilation_flags = []
additional_flags = []
possible_targets = ['dev', 'stable']
target = 'dev'

# Example usage: scons target=dev,stable #
if 'target' in ARGUMENTS:
    target = str(ARGUMENTS['target']).lower()
if not target in possible_targets:
    target = 'dev'

base_compilation_flags.append('-DTARGET=' + target.upper())

# Enviroment Setup #
env = Environment(
    COMPILATIONDB_USE_ABSPATH=True,
    CPPPATH=['#/include', '#/include/vendor', '#/include/vendor/lua'],
    SCONS_C_STANDARD='c17',
    CCFLAGS=base_compilation_flags
)

platform = env['PLATFORM']
bin_target = 'build/' + target + '/' + platform + '/bin/'
build_target = 'build/' + target + '/' + platform + '/obj/'

match platform:
    case 'win32': # Windows
        match target:
            case 'stable':
                additional_flags = ['/O2', '/MT', '/EHsc']
                env.Append(LINKFLAGS = ['/SUBSYSTEM:WINDOWS', '/entry:mainCRTStartup'],)
            case 'dev':
                additional_flags =['/DEBUG', '/Od', '/MTd', '/EHsc']
        env.Append(
            CCFLAGS = additional_flags,
            LINKFLAGS = ['/NODEFAULTLIB:library'],
            LIBPATH = ['#/lib/win32'],
            LIBS = ['raylibdll'],
        )
    case _: # Linux (not sure the actual value for linux atm)
        match target:
            case 'stable':
                additional_flags = ['-O3', '-Wall']
            case 'dev':
                additional_flags =['-g', '-O0', '-Wall']
        env.Append(
            CCFLAGS = additional_flags,
            LIBPATH=['#/lib'],
            LIBS = ['raylib'],
        )

# Compatibility with certain things #
# Example usage: scons compile_commands=1 #
if 'compile_commands' in ARGUMENTS:
    env.Tool('compilation_db')
    env.CompilationDatabase()

# Exports #

Export('env')
Export('build_target')

# Compilation #
SConscript('src/SConscript', exports='env', variant_dir='#/' + build_target, duplicate=0)
env.Program(target=bin_target + 'Funkin', source=Glob('#/' + build_target + '**.o**') + Glob('#/' + build_target + '**.lib'))

# Assets #

# we use shutil because scons itself was hard to get working this specific way, sorry!
import shutil
shutil.copytree(src = 'assets', dst = bin_target + 'assets', dirs_exist_ok = True)

if platform == 'win32':
    shutil.copyfile(src = 'lib/' + platform + '/raylib.dll', dst = bin_target + 'raylib.dll')
