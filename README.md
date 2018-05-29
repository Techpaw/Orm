## About
That's experimental Cpp ORM

## Installation
1. Add `https://api.bintray.com/conan/trigger-happy/conan-packages` to your conan repos:
```
conan remote add trigger-happy "https://api.bintray.com/conan/trigger-happy/conan-packages"
```
2. Add `https://api.bintray.com/conan/bincrafters/public-conan` to your conan repos:
```
conan remote add bincrafters "https://api.bintray.com/conan/bincrafters/public-conan"
```
3. Mac users will need to follow these instructions to fix libssh errors:
https://solitum.net/openssl-os-x-el-capitan-and-brew/
4. Add `https://api.bintray.com/conan/techpaw/SolutionsForWeb` to you conan repos list:
```
conan remote add techpaw/SolutionsForWeb https://api.bintray.com/conan/techpaw/SolutionsForWeb
```
5. Install packages
```
conan install . --build=missing
```