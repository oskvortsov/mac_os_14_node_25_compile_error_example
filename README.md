## Build Error with NAN on macOS Darwin 23.6.0 and Node.js v25.2.1

### Description

I'm encountering a compilation error when trying to install a native Node.js addon using NAN (Native Abstractions for Node.js) on macOS. The error occurs during `npm install` when node-gyp attempts to rebuild the native module.

### Environment

- **OS**: macOS Darwin 23.6.0
- **Node.js**: v25.2.1
- **node-gyp**: v10.3.1 (in error) / v12.1.0 (global)
- **Python**: 3.14.2
- **Xcode Select**: version 2408
- **Compiler**: Apple clang version 16.0.0 (clang-1600.0.26.6)
- **NAN**: ^2.18.0

### Error Output

```
gyp ERR! build error 
gyp ERR! stack Error: `make` failed with exit code: 2
gyp ERR! stack at ChildProcess.<anonymous> (/Users/user/Projects/node_25_compile_error/node_modules/node-gyp/lib/build.js:216:23)
gyp ERR! System Darwin 23.6.0
gyp ERR! command "/Users/user/.nvm/versions/node/v25.2.1/bin/node" "/Users/user/Projects/node_25_compile_error/node_modules/.bin/node-gyp" "rebuild"
gyp ERR! cwd /Users/user/Projects/node_25_compile_error
gyp ERR! node -v v25.2.1
gyp ERR! node-gyp -v v10.3.1
gyp ERR! not ok 
npm error code 1
npm error path /Users/user/Projects/node_25_compile_error
npm error command failed
npm error command sh -c node-gyp rebuild
```

### Compilation Errors

The build fails with multiple errors in V8 headers:

```
In file included from ../hello.cc:1:
In file included from ../node_modules/nan/nan.h:67:
In file included from /Users/user/Library/Caches/node-gyp/25.2.1/include/node/node.h:74:
In file included from /Users/user/Library/Caches/node-gyp/25.2.1/include/node/v8.h:24:
In file included from /Users/user/Library/Caches/node-gyp/25.2.1/include/node/v8-array-buffer.h:14:
/Users/user/Library/Caches/node-gyp/25.2.1/include/node/v8-object.h:957:37: error: expected expression
  957 |         I::ReadExternalPointerField<{internal::kFirstEmbedderDataTag,
      |                                     ^
/Users/user/Library/Caches/node-gyp/25.2.1/include/node/v8-object.h:980:37: error: expected expression
  980 |         I::ReadExternalPointerField<{internal::kFirstEmbedderDataTag,
      |                                     ^
../hello.cc:37:23: error: no member named 'sleep_for' in namespace 'std::this_thread'
   37 |     std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds_));
      |     ~~~~~~~~~~~~~~~~~~^
5 errors generated.
make: *** [Release/obj.target/addon/hello.o] Error 1
```

### Reproducible Example

A minimal reproducible example can be found here: **[YOUR_GITHUB_REPO_URL]**

### Steps to Reproduce

1. Clone the repository
2. Run `npm install`
3. Observe the compilation error

### Expected Behavior

The native addon should compile successfully and install without errors.

### Actual Behavior

The compilation fails with V8 API compatibility errors and C++ standard library issues.

### Possible Cause

This appears to be a compatibility issue between:
- Node.js v25.2.1 (very recent version)
- NAN v2.18.0
- The new V8 API changes in Node.js 25.x
- Apple Clang 16.0.0 on macOS

### Question

Is there a known compatibility issue with NAN and Node.js v25.x? Should I downgrade to an LTS version of Node.js, or is there a workaround for this?

Any help would be appreciated!
