project('dwhbll-portable', 'cpp', default_options: ['cpp_std=c++26'])

cpp = meson.get_compiler('cpp')
reflection = ['-freflection']

python_module = import('python')
python = python_module.find_installation('python3', required: false)
if python.found()
  codegen_python = [python]
else
  uv = find_program('uv', required: false)
  if uv.found()
    # Resolve managed Python at build time so uv upgrades leave no stale Ninja dependency.
    codegen_python = [uv, '--quiet', 'run', '--no-project', '--python', '3.13', '--', 'python']
  else
    codegen_python = [python_module.find_installation('python', required: true)]
  endif
endif

ucd = custom_target(
  'dwhbll-ucd',
  input: 'script/unicode/fetch.py',
  output: 'UCD.zip',
  command: codegen_python + ['@INPUT@', '@OUTPUT@'],
)
unicode_tables = custom_target(
  'dwhbll-unicode-tables',
  input: ucd,
  output: 'unicode_tables.cpp',
  command: codegen_python + ['-m', 'script.unicode.generate_tables', '@INPUT@', '@OUTPUT@'],
  env: {'PYTHONPATH': meson.current_source_dir()},
  depend_files: files(
    'script/__init__.py',
    'script/unicode/generate_tables.py',
    'script/codegen/__init__.py',
    'script/codegen/file.py',
    'script/codegen/namespace.py',
  ),
)

headers = include_directories('include')
runtime_deps = [dependency('threads'), cpp.find_library('stdc++exp')]
# Linux/POSIX backends (io_uring, sockets, subprocesses, mmap, affinity, and
# perf events) and the separate HIP target are outside this source list.
dwhbll_portable = static_library(
  'dwhbll-portable',
  'src/dwhbll/cli/arg.cpp',
  'src/dwhbll/cli/argmatches.cpp',
  'src/dwhbll/cli/command.cpp',
  'src/dwhbll/cli/parser.cpp',
  'src/dwhbll/collections/cache.cpp',
  'src/dwhbll/collections/memory_buffer.cpp',
  'src/dwhbll/concurrency/coroutine/cancellable_base.cpp',
  'src/dwhbll/concurrency/coroutine/detached_task.cpp',
  'src/dwhbll/concurrency/spinlock.cpp',
  'src/dwhbll/console/logging.cpp',
  'src/dwhbll/debug/debug.cpp',
  'src/dwhbll/debug/panic.cpp',
  'src/dwhbll/debug/perf.cpp',
  'src/dwhbll/cryptography/arc4/arc4.cpp',
  'src/dwhbll/cryptography/hash/sha1.cpp',
  'src/dwhbll/exceptions/rt_exception_base.cpp',
  'src/dwhbll/files/executables/mz.cpp',
  'src/dwhbll/files/executables/pe.cpp',
  'src/dwhbll/files/filejar/file.cpp',
  'src/dwhbll/files/filejar/file_mgr.cpp',
  'src/dwhbll/files/parse_utils.cpp',
  'src/dwhbll/graphics/bitmap.cpp',
  'src/dwhbll/json/json.cpp',
  'src/dwhbll/lang/c/tokenize.cpp',
  'src/dwhbll/lang/common.cpp',
  'src/dwhbll/lang/common/file_stream.cpp',
  'src/dwhbll/lang/cpp/cpp_raw_stream.cpp',
  'src/dwhbll/lang/cpp/preprocess/line_splice_stream.cpp',
  'src/dwhbll/math/vec4.cpp',
  'src/dwhbll/network/address.cpp',
  'src/dwhbll/sanify/deferred.cpp',
  'src/dwhbll/testing/harness.cpp',
  'src/dwhbll/testing/runner.cpp',
  'src/dwhbll/testing/testing.cpp',
  'src/dwhbll/unicode/helpers.cpp',
  'src/dwhbll/uuid/uuid.cpp',
  unicode_tables,
  include_directories: headers,
  cpp_args: reflection,
  dependencies: runtime_deps,
)
dwhbll_dep = declare_dependency(
  link_with: dwhbll_portable,
  include_directories: headers,
  compile_args: reflection,
  dependencies: runtime_deps,
)
