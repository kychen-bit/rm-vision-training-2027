# 使用方法

```bash
cmake -S . -B build
cmake --build build
printf '2 1 90 1 -1\n' | ./build/transform
```

目前 `transform()` 是未实现的 TODO。编译通过只是第一步；你需要让输出符合 W02 的三组测试。禁止将 TODO 原样提交作为已完成答案。
