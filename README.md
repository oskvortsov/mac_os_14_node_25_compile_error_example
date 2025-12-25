# NAN Example - Not Working on Current macOS

⚠️ **Warning:** This code does not work on the current version of macOS.

There are compatibility issues with native Node.js addons on recent macOS versions.

## Environment Versions

- **Python**: 3.14.2
- **Xcode Select**: 2408
- **G++**: Apple clang version 16.0.0 (clang-1600.0.26.6)
- **node-gyp**: v12.1.0
- **Node.js**: v25.2.1
- **macOS**: Darwin 23.6.0

## Error Details

The error occurs when running `npm install`:

```
gyp ERR! build error 
gyp ERR! stack Error: `make` failed with exit code: 2
gyp ERR! stack at ChildProcess.<anonymous> (/Users/test/node_25_compile_error/node_modules/node-gyp/lib/build.js:216:23)
gyp ERR! System Darwin 23.6.0
gyp ERR! command "/Users/olegskvortsov/.nvm/versions/node/v25.2.1/bin/node" "/Users/test/node_25_compile_error/node_modules/.bin/node-gyp" "rebuild"
gyp ERR! cwd /Users/test/node_25_compile_error
gyp ERR! node -v v25.2.1
gyp ERR! node-gyp -v v10.3.1
gyp ERR! not ok 
npm error code 1
npm error path /Users/test/node_25_compile_error
npm error command failed
npm error command sh -c node-gyp rebuild
npm error A complete log of this run can be found in: /Users/test/.npm/_logs/2025-12-25T12_20_55_595Z-debug-0.log
```

