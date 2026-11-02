# 算法竞赛题解集

基于 [Typst](https://typst.app) 的算法竞赛题解 / 习题册模板。通过统一的脚本，可以把分散的题面、题解、代码编译成单个 PDF 大合集，也可以单独编译某场比赛或某道题。

## 快速开始

```bash
# 编译全部（大合集 + 所有比赛 + 所有单题）
./build.sh

# 只编译大合集
./build.sh index

# 只编译某场比赛
./build.sh contest Contest/abc480

# 只编译某道题
./build.sh problem Contest/abc480/e/main.typ

# 关闭题解（习题册样式，只保留题面）
SOLUTION=off ./build.sh
```

所有输出都放在 `build/` 目录，目录结构镜像源文件。

> 手动编译单个文件时记得加 `--root .`，例如：
> ```bash
> typst compile Contest/abc480/e/main.typ out.pdf --root .
> ```

## 目录结构

```
.
├── build.sh                 # 一键编译脚本
├── typst.toml               # 包信息
├── config.typ               # 全局配置（开关与文案）
├── lib.typ                  # 共享函数（make-problem / code-block 等）
├── style.typ                # 样式注入点（字体、代码块外观等）
├── index.typ                # 大合集入口
└── Contest/                 # 比赛根目录
    ├── <contest-id>/        # 一场比赛（如 AAAsample、abc480）
    │   ├── main.typ         # 比赛入口（标题 + 汇总各题）
    │   └── <problem-id>/    # 一道题（如 a、b、e）
    │       ├── main.typ     # 题目入口（组装题面 + 题解）
    │       ├── <problem-id>.prob.typ   # 题面
    │       ├── <problem-id>.sol.typ    # 题解
    │       └── <problem-id>.cpp        # 参考代码
    └── ...
```

## 文件组织规范

### 命名约定

- 比赛目录名 = 比赛 id，如 `AAAsample`、`abc480`。
- 题目目录名 = 题目 id（单个小写字母或题号），如 `a`、`b`、`e`。
- 同一题目目录内，题面 / 题解 / 代码三个文件的文件名必须与 `problem-id` 一致：

  ```
  <problem-id>.prob.typ
  <problem-id>.sol.typ
  <problem-id>.cpp
  ```

  例如题目 id 为 `e` 时，文件必须是 `e.prob.typ`、`e.sol.typ`、`e.cpp`。

### 导入路径（务必按目录层级写对）

| 文件位置 | 导入 `lib.typ` 的路径 |
| --- | --- |
| 比赛入口 `Contest/<cid>/main.typ` | `../../lib.typ` |
| 题目文件 `Contest/<cid>/<pid>/*.typ` | `../../../lib.typ` |

> `index.typ` 位于根目录，直接 `#import "lib.typ": *`。

## 添加一道题

以在比赛 `AAAsample` 下添加题目 `c` 为例：

1. 新建目录 `Contest/AAAsample/c/`。

2. 新建 `Contest/AAAsample/c/main.typ`（题目入口）：

   ```typ
   #import "../../../lib.typ": *

   #let contest-id = "AAAsample"      // 比赛 id（直接写死，勿 import 比赛入口）
   #let problem-id = "c"              // 题目 id
   #let title = "题目名称"             // 题目标题

   #let statement = include problem-id + ".prob.typ"
   #let solution = include problem-id + ".sol.typ"

   #let content_ = title_ => make-problem(
     contest-id: contest-id,
     problem-id: problem-id,
     title: title_,
     statement: statement,
     solution: solution,
   )
   #let content = content_(upper(problem-id) + "." + title)

   #show: article

   #content_(contest-id + " " + upper(problem-id) + "." + title)()
   ```

3. 新建 `Contest/AAAsample/c/c.prob.typ`（题面）：

   ````typ
   #import "../../../lib.typ": section

   === 题目描述
   题目正文……

   === 输入格式
   ……

   === 输出格式
   ……

   === 样例

   ==== 1.in / 1.out

   ```
   输入内容……
   ```

   ```
   输出内容……
   ```
   ````

4. 新建 `Contest/AAAsample/c/c.sol.typ`（题解）：

   ```typ
   #import "../../../lib.typ": code-block

   题解正文……

   #code-block(read("c.cpp"))
   ```

5. 新建 `Contest/AAAsample/c/c.cpp`（参考代码）。

6. 在比赛入口 `Contest/AAAsample/main.typ` 中导入并挂载这道题：

   ```typ
   #import "c/main.typ": content as c

   #let contest = () => [
     = #title
     #a()
     #b()
     #c()
   ]
   ```

完成。运行 `./build.sh` 即可看到新增题目。

## 录入题目内容（读题与翻译）

题面内容通常来自 AtCoder 等 OJ。录入流程：

1. 抓取英文题面。AtCoder 题目页（`https://atcoder.jp/contests/<cid>/tasks/<cid>_<pid>?lang=en`）可能无法通过 `web_fetch` 访问（域名解析为非公网 IP），此时用 `curl` 抓取：

   ```bash
   curl -sS -A "Mozilla/5.0" \
     "https://atcoder.jp/contests/abc481/tasks/abc481_e?lang=en" \
     -o /tmp/abc481_e.html
   ```

2. 从 HTML 的 `lang-en` 区块提取各小节（Problem Statement / Constraints / Input / Output / Sample）。其中 `<var>…</var>` 是数学公式，`<pre>…</pre>` 是输入输出格式与样例。

3. 翻译为中文并填入 `*.prob.typ`：

   - 标题 `title` 保留 AtCoder 原始英文标题；
   - 小节标签用中文：`题目描述 / 约束条件 / 输入格式 / 输出格式 / 样例`；
   - 数学公式改写为 Typst 数学：`\le`→`<=`、`\ge`→`>=`、`\ne`→`!=`、`\times`→`times`、`\dots`→`dots` 等。

4. 输入输出格式与样例统一用 `` ``` `` 代码围栏（不要用 `#raw`），例如：

   ````typ
   ==== 1.in / 1.out

   ```
   1 2
   ```

   ```
   3
   ```
   ````

## 添加一场比赛

以添加比赛 `abc999`（含题目 `a`）为例：

1. 新建目录 `Contest/abc999/a/`，并按「添加一道题」的第 2~5 步创建四个文件（注意 `contest-id` 写 `"abc999"`，`problem-id` 写 `"a"`）。

2. 新建比赛入口 `Contest/abc999/main.typ`：

   ```typ
   #import "../../lib.typ": *

   #let title = "abc999"

   #import "a/main.typ": content as a

   // 供大合集导入：作为一节（比赛标题 + 各题）
   #let contest = () => [
     = #title
     #a()
   ]

   // 单独编译本场比赛（单级目录）
   #show: article
   #contest()
   ```

3. 在大合集入口 `index.typ` 中导入并挂载这场比赛：

   ```typ
   #import "Contest/abc999/main.typ" as contest_abc999

   #show: article
   #set document(title: "算法竞赛题解集")
   #outline(title: outline-title, depth: 2)

   #contest_abc999.contest()
   ```

> 如果某场比赛暂时只维护单题、不需要比赛入口，也可以省略第 2、3 步，仅创建题目目录；`./build.sh` 仍会自动编译该单题。

## 配置说明

所有开关与文案集中在 `config.typ`：

- `show-solution`：是否显示题解（`true` = 题解，`false` = 习题册）。编译时可用 `--input show-solution=false` 临时覆盖。
- `solution-title`：题解小标题文案（默认「题解」）。
- `outline-title`：目录标题文案（默认「目录」）。

所有样式集中在 `style.typ` 的 `article()` 函数体内（字体、字号、代码块外观等），`set` / `show` 规则必须写在这里才能生效。

## 依赖

- [Typst](https://typst.app)（编译引擎）
- 字体：`LXGW WenKai`（霞鹜文楷，中文回退字体，可在 `style.typ` 中替换为你系统中已安装的中文字体）
- Typst 包：`@preview/codly:1.3.0`、`@preview/codly-languages:0.1.1`（代码高亮，首次编译会自动下载）
