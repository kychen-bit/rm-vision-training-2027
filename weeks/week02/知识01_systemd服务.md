# W02 专题知识 01：systemd 系统级开机自启

## 先想一个 RoboMaster 问题

假设 NUC 装在步兵上：你在终端里输入 `./auto_aim` 才能运行视觉程序。如果每次上电都要手动打开终端，或程序崩溃后无人恢复，会增加比赛准备与调试成本。**systemd** 就是 Linux 中常见的服务管理器，负责在合适的时机启动程序、跟踪状态、收集日志，并可在特定退出条件下重启它。

这周只管理**无硬件副作用的模拟程序**；不要把实车控制/发射程序直接设为开机自启。

## 你应该理解的 5 个概念

| 名称 | 作用 | 常见误解 |
|---|---|---|
| `service` | 一个由 systemd 管理的进程及其配置 | 不是任意 `.sh` 都是系统服务 |
| `systemctl start` | 现在启动一个服务 | 不等于下次开机自动运行 |
| `systemctl enable` | 配置启动时的依赖链接（基于 Install 信息） | 不保证立即启动，也不保证程序可执行 |
| `systemctl status` | 查看当前状态与最近输出 | active 不保证业务逻辑正确 |
| `journalctl -u` | 查询指定服务日志 | 不是只适用于系统报错 |

> 区别 system 级与 user 级：本周要求 `/etc/systemd/system/` 下的**系统级服务**。出于最小权限原则，示例服务使用普通用户执行。不要以 root 运行任意网络下载的脚本。

## 实践前先做环境检查

在**真实 Ubuntu** 终端执行：

```bash
ps -p 1 -o comm=
systemctl --version
whoami
```

期望 PID 1 由 `systemd` 管理。若输出不是 systemd，请先查清本机启动方式再继续。WSL2 上可以启用 systemd，但 **启动 WSL 实例 ≠ Windows 整机开机自启**，不能用 WSL 测试冒充 Ubuntu 双系统的开机验证。

## 标准操作流程（安全可复现）

示例程序已经放在 `examples/week02/heartbeat.py` 中，每 5 秒打印一次时间。请先阅读程序，并解释为什么它会持续运行。

**第一步：创建固定路径。** 把项目文件保存到自己的 Ubuntu 主目录，例如 `~/rm_training/week02/heartbeat.py`，绝对路径可通过 `realpath` 获得：

```bash
mkdir -p ~/rm_training/week02
cp examples/week02/heartbeat.py ~/rm_training/week02/heartbeat.py
realpath ~/rm_training/week02/heartbeat.py
/usr/bin/python3 -u ~/rm_training/week02/heartbeat.py
# 看到输出后按 Ctrl+C 停止
```

**第二步：准备配置文件。** 按提供的 `examples/week02/vision-heartbeat.service.in` 新建 `vision-heartbeat.service`；将 `<用户名>`、`<绝对路径>` 逐一替换为本机真实值（不要保留尖括号）。

```ini
[Unit]
Description=RM Vision Training Heartbeat (safe demo)
After=multi-user.target

[Service]
Type=simple
User=<用户名>
WorkingDirectory=<绝对路径的文件夹>
ExecStart=/usr/bin/python3 -u <绝对路径>/heartbeat.py
Restart=on-failure
RestartSec=3

[Install]
WantedBy=multi-user.target
```

字段说明：`[Unit]` 写服务元信息/顺序；`[Service]` 写程序如何运行；`[Install]` 告诉 enable 创建何种启动依赖。`Restart=on-failure` 仅在失败等条件下重启，不代表手工 stop 后一定立即重启。

**第三步：安装、重载、启动、看日志。**

```bash
sudo cp vision-heartbeat.service /etc/systemd/system/vision-heartbeat.service
sudo systemctl daemon-reload
sudo systemctl start vision-heartbeat.service
systemctl status vision-heartbeat.service
journalctl -u vision-heartbeat.service -n 20 --no-pager
```

`daemon-reload` 是让 systemd 重新读取单元配置文件；它与重启服务是两回事。只要能手动启动，就说明目前服务配置初步正确，但**还不代表开机自启成功**。

**第四步：启用、真正重启验证。**

```bash
sudo systemctl enable vision-heartbeat.service
systemctl is-enabled vision-heartbeat.service
# 保存好其他工作后，实际重启 Ubuntu 再验证
sudo reboot
```

重启后（普通终端即可）查看：

```bash
systemctl status vision-heartbeat.service
journalctl -b -u vision-heartbeat.service -n 30 --no-pager
```

`-b` 用于看当前 boot 的日志。**不要求把开机服务留在自己电脑上**，验收后清理。

**第五步：主动清理（必做）。**

```bash
sudo systemctl disable --now vision-heartbeat.service
sudo rm /etc/systemd/system/vision-heartbeat.service
sudo systemctl daemon-reload
```

只删除自己本周创建的这个服务文件，不得复制网上的批量“清理所有 systemd 服务”命令。

## 故障排查速查

| 现象 | 首先排查 |
|---|---|
| Unit ... not found | 名称拼写、是否复制到 `/etc/systemd/system`、是否 `daemon-reload` |
| `203/EXEC` | `ExecStart` 路径与可执行文件是否存在、权限是否正确 |
| `200/CHDIR` | `WorkingDirectory` 是否存在；普通用户是否可进入 |
| 运行一会儿立刻退出 | 程序是否正常结束；`Type=simple` 下预期是持续进程 |
| enable 后不工作 | 要分开检查 `is-enabled` 和 `status`；先看 `journalctl` |
| 重启后没日志 | 是否真实重启了 Ubuntu、当前 boot 是否有运行、服务是否启用 |

## 你需要能讲清楚

1. `start` 和 `enable` 区别是什么？
2. 为什么 `ExecStart` 使用**绝对路径**？
3. `User` 为什么不推荐默认 root？
4. 为什么程序打日志比“看见一次启动成功”重要？
5. 如果自瞄程序真实需要相机设备就绪，该如何设计前置条件，而不是盲目在开机瞬间启动？（思考题，不用实做）

## 官方资料

- [systemd.service 文档](https://www.freedesktop.org/software/systemd/man/latest/systemd.service.html)
- [systemd.unit 文档](https://www.freedesktop.org/software/systemd/man/latest/systemd.unit.html)
- [systemctl 文档](https://www.freedesktop.org/software/systemd/man/latest/systemctl.html)
- [journalctl 文档](https://www.freedesktop.org/software/systemd/man/latest/journalctl.html)
