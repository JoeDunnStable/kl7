project('kl7', 'cpp', default_options : ['cpp_std=c++11'],
         version : '1.0')

compiler=meson.get_compiler('cpp').get_id()

if compiler == 'gcc' or compiler == 'clang'
  add_global_arguments([
    '-Wno-non-virtual-dtor' ],
    language: 'cpp')
elif compiler == 'msvc'
endif


#Boost header and some libraries.
#I had to define BOOST_ROOT to get this to work.
boostdep = dependency('boost', modules : ['program_options', 'filesystem', 'system'],  required : true)

incdir=include_directories(['kl7-cli',
                            'test-kl7'])
subdir('doc')
subdir('kl7-cli')
subdir('test-kl7')

