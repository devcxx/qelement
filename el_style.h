#ifndef EL_STYLE_H
#define EL_STYLE_H

#include "el_global.h"

EL_BEGIN_NAMESPACE

// Color 色彩
// https://e3.shengxinjing.cn/#/component/color
namespace Color {
// 主色
const Q_DECL_UNUSED char Brand[] = "#409EFF";
// 辅助色 除了主色外的场景色，需要在不同的场景中使用（例如危险色表示危险的操作）
const Q_DECL_UNUSED char Success[] = "#67C23A";
const Q_DECL_UNUSED char SuccessDisabled[] = "#b3e19d";
const Q_DECL_UNUSED char Warning[] = "#E6A23C";
const Q_DECL_UNUSED char WarningDisabled[] = "#f3d19e";
const Q_DECL_UNUSED char Danger[] = "#F56C6C";
const Q_DECL_UNUSED char DangerDisabled[] = "#fab6b6";
const Q_DECL_UNUSED char Info[] = "#909399";
const Q_DECL_UNUSED char InfoDisabled[] = "#c8c9cc";
// 中性色
// 中性色用于文本、背景和边框颜色。通过运用不同的中性色，来表现层次结构
// 主要文字
const Q_DECL_UNUSED char PrimaryText[] = "#303133";
const Q_DECL_UNUSED char PrimaryTextDisabled[] = "#a0cfff";
// 常规文字
const Q_DECL_UNUSED char DefaultText[] = "#606266";
const Q_DECL_UNUSED char DefaultTextDisabled[] = "#c0c4cc";
// 次要文字
const Q_DECL_UNUSED char SecondaryText[] = "#909399";
//占位文字
const Q_DECL_UNUSED char PlaceholderText[] = "#C0C4CC";
}

// Border 边框
// https://e3.shengxinjing.cn/#/component/border
namespace Border {
// 无圆角
const Q_DECL_UNUSED int None = 0;
// 小圆角
const Q_DECL_UNUSED int Small = 2;
// 大圆角
const Q_DECL_UNUSED int Big = 4;
// 圆形圆角
const Q_DECL_UNUSED int Circle = 30;
}

// 字号 (像素px)
namespace FontSize {
// 辅助文字
const Q_DECL_UNUSED int ExtraSamll = 12;
// 正文（小）
const Q_DECL_UNUSED int Samll = 13;
// 正文
const Q_DECL_UNUSED int Base = 14;
// 小标题
const Q_DECL_UNUSED int Medium = 16;
// 标题
const Q_DECL_UNUSED int Large = 18;
// 主标题
const Q_DECL_UNUSED int ExtraLarge = 20;
}

EL_END_NAMESPACE

#endif // EL_STYLE_H
