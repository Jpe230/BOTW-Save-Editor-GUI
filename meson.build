project('BOTW_Save_Editor', ['c', 'cpp'],
    version: '0.4.0',
    default_options: [ 'buildtype=release', 'strip=true', 'b_ndebug=if-release', 'cpp_std=c++1z' ],
)

subdir('borealis/library')

source_files = files(
    'src/main.cpp',
    'src/BTWE/File.cpp',
    'src/BTWE/SaveFileEditor.cpp',
    'src/BTWE/Container.cpp',

)

BOTW_Save_Editor = executable(
    'BOTW_Save_Editor',
    [ source_files, borealis_files ],
    dependencies : borealis_dependencies,
    install: true,
    include_directories: [ borealis_include, include_directories('src')],
    cpp_args: [ '-g', '-O2', '-DBOREALIS_RESOURCES="./resources/"' ]
)
