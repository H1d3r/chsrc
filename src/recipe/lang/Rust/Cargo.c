/** ------------------------------------------------------------
 * SPDX-License-Identifier: GPL-3.0-or-later
 * -------------------------------------------------------------
 * File Authors  : Aoran Zeng <ccmywish@qq.com>
 * Contributors  :  Nil Null  <nil@null.org>
 * Created On    : <2023-08-30>
 * Last Modified : <2024-10-02>
 * ------------------------------------------------------------*/

/**
 * @update 2024-10-02
 * @note 以下都支持稀疏索引，我们换源时都将默认添加 `sparse+`
 * @note 链接末尾的 `/` 不能缺少
 */
static SourceInfo
pl_rust_cargo_sources[] = {
  {&Upstream,      "https://index.crates.io/"}, // @help 是这个吗？
  {&MirrorZ,       "https://mirrors.cernet.edu.cn/crates.io-index/"},
  {&Sjtug_Zhiyuan, "https://mirrors.sjtug.sjtu.edu.cn/crates.io-index/"},
  {&Tuna,          "https://mirrors.tuna.tsinghua.edu.cn/crates.io-index/"},
  {&Bfsu,          "https://mirrors.bfsu.edu.cn/crates.io-index/"},
  {&Ustc,          "https://mirrors.ustc.edu.cn/crates.io-index/"},
  {&RsProxyCN,     "https://rsproxy.cn/index/"},
  {&Hust,          "https://mirrors.hust.edu.cn/crates.io-index/"}
};
def_sources_n(pl_rust_cargo);


/**
 * chsrc get cargo
 */
void
pl_rust_cargo_getsrc (char *option)
{
  chsrc_view_file ("~/.cargo/config.toml");
}


/**
 * @consult https://mirrors.tuna.tsinghua.edu.cn/help/crates.io-index/
 * @consult https://help.mirrors.cernet.edu.cn/crates.io-index
 *
 * chsrc set cargo
 */
void
pl_rust_cargo_setsrc (char *option)
{
  chsrc_yield_source_and_confirm (pl_rust_cargo);

  const char* file = xy_strjoin (3,
    "[source.crates-io]\n"
    "replace-with = 'mirror'\n\n"

    "[source.mirror]\n"
    "registry = \"sparse+", source.url, "\"");

  chsrc_note2 (xy_strjoin (3, "请您手动写入以下内容到 ", xy_uniform_path ("~/.cargo/config.toml"), " 文件中:"));
  puts (file);
  chsrc_conclude (&source, SetsrcType_Manual);
}


/**
 * chsrc reset cargo
 */
void
pl_rust_cargo_resetsrc (char *option)
{
  pl_rust_cargo_setsrc (SetsrcType_Reset);
}


FeatInfo
pl_rust_cargo_feat (char *option)
{
  FeatInfo f = {0};

  f.can_get = true;
  f.can_reset = true;

  f.cap_locally = PartiallyCan;
  f.cap_locally_explain = "可以基于本项目换源吗？请帮助确认";
  f.can_english = false;
  f.can_user_define = true;

  f.note = NULL;
  return f;
}


def_target_gsrf(pl_rust_cargo);
