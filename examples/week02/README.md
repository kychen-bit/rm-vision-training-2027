# W02 参考材料（安全演示，不是完整答案）

- `heartbeat.py`：无硬件副作用的常驻打印程序，用于理解 systemd。
- `vision-heartbeat.service.in`：systemd **模板**，需替换用户名、工作目录与绝对路径。
- `transform_starter/`：可编译的 C++17 起步骨架，`transform()` **尚未实现**，需要自行完成。

请不要照抄包含 `<用户名>` 的 service 文件直接启用。仅在自己电脑上测试，完成后清理服务。
