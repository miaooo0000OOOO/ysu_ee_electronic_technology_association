在Ubuntu系统上安装pandoc

```bash
sudo apt install pandoc
```

安装texlive

```bash
sudo apt-get install texlive-full
```

列出中文字体

```bash
 fc-list :lang=zh
```

在字体文件路径之后，逗号之前的是字体名

`Noto Sans CJK SC`是微软雅黑

在终端运行命令

```bash
pandoc --pdf-engine=xelatex -V CJKmainfont="Noto Sans CJK SC"  input.md -o output.pdf
```