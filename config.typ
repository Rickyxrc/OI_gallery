// ============================================================
//  全局配置：开关与文案
// ============================================================

// 是否显示题解。改成 false 即为"习题册"样式（只保留题面）。
// 也可以不改这个文件，在编译时用命令行覆盖：
//   typst compile index.typ --input show-solution=false
#let show-solution = (sys.inputs.at("show-solution", default: "true") == "true")

// 题解小标题文案
#let solution-title = "题解"

// 目录标题文案
#let outline-title = "目录"
