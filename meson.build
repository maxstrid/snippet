project(
  'snippet',
  'cpp',
  version : '0.1',
  default_options : [
    'warning_level=3',
    'cpp_std=c++17',
    'werror=true',
    'optimization=1',
])

boost = dependency('boost')
tomlplusplus = dependency('tomlplusplus')

executable('snippet',
           'src/main.cc', 'src/config.cc',
           install : true,
           dependencies : [boost, tomlplusplus]
          )
