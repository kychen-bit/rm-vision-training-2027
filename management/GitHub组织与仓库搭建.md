# GitHub 组织与培训仓库：建议的最小配置

## 要不要创建 Organization？

**建议创建**。它把仓库所有权从个人账号转为队内集体管理；方便下一届新生继承，未来还能添加导航/雷达等团队。当前先建 **1 个私有培训仓库**，不需搭官网、Actions 或复杂权限。

## 第一次设置步骤

1. 打开 [GitHub 创建组织官方说明](https://docs.github.com/en/organizations/collaborating-with-groups-in-organizations/creating-a-new-organization-from-scratch)，创建 GitHub Free Organization。**组织命名建议用战队/学校正式英文名**，不要只写“自瞄”，便于跨年。
2. 至少设置 **2 名可信主力为 Owner**，避免单人毕业或账号丢失。邀请 4 名新人为普通成员。
3. 创建 **private** 仓库：`rm-vision-training-2027`。创建一个 `vision-trainees` Team（普通成员），再给它仓库写权限。
4. 解压本文件夹，将**里面的文件**上传仓库根目录，默认分支 `main`。
5. 新人一人一个分支：`student/<github-id>/week02`，作业目录 `submissions/<github-id>/week02/`。
6. 新人推送分支并提交 Pull Request 到 `main`；主力 review 后再合并。参见 [PR 文档](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/about-pull-requests)。

## 第一次提交常用命令

```bash
git clone https://github.com/<组织名>/rm-vision-training-2027.git
cd rm-vision-training-2027
git switch -c student/<自己的github-id>/week02
mkdir -p submissions/<自己的github-id>/week02
# 完成自己的代码和 README 后
git add submissions/<自己的github-id>/week02
git commit -m 'W02: 完成 systemd 和坐标变换任务'
git push -u origin student/<自己的github-id>/week02
```

GitHub 仓库网页里选择 **Compare & pull request**；不要所有人直接改 main。

## GitHub Free 的一个实际限制

GitHub 官方文档目前说明：**免费组织上的分支保护/Rulesets 主要可用于 public 仓库；private 仓库的强制保护需要相应付费方案**。因此本队如保持 private，先靠约定遵守“PR 后由主力合并”，不应宣称可以免费强制锁定 main。更严格的权限隔离可改用学生个人 fork + 主库只读、或者后续评估方案。

## 现在不要做的事情

- 不要一口气建立 W01～W14 共 14 个独立仓库；一个 repo 已足够。
- 不要公开赛季未授权视频、相机标定文件、内部通讯协议、token 等。
- 不要把生产比赛代码与新人培训作业合在一起。
- GitHub Issues/Projects/Actions 能用，但先以 Markdown、PR 为中心，避免管理成本超过培训收益。
