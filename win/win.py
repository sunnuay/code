# gradio==3.50.2
# networkx
# pymupdf

import gradio as gr
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import networkx as nx
import fitz
import random
import json


def read(file, input):
    try:
        doc = fitz.open(file[0])
        page = doc.load_page(int(input))
        return page.get_text("text")
    except Exception as e:
        return e


def find(book, year, type, input):
    columns = ["booktitle", "year", "pages", "author", "title", "ee", "abstract"]
    list = [pd.DataFrame(columns=columns)]
    for b in book:
        for y in year:
            list.append(pd.read_csv(f".local/data/{b}/{b}_{y}.csv"))
    df = pd.concat(list)
    df = df[df[type].str.contains(input, case=False)]
    df = df.drop(columns="abstract")
    return df


def plot(df):
    plt.clf()
    n, m = 10, 5
    width = [random.randint(1, m) for _ in range(m)]
    G = nx.gnm_random_graph(n, m)
    pos = nx.circular_layout(G)
    nx.draw(G, pos, with_labels=True, width=width)
    return "", plt.gcf()


def recommend(df, input):
    plt.clf()
    width = []
    string = ""
    row = df[df["title"].str.contains(input, case=False)].head(1)
    value1 = row["vector"].values[0]
    vector1 = np.array(json.loads(value1))
    for i, value2 in df["vector"].items():
        vector2 = np.array(json.loads(value2))
        similarity = np.dot(vector1, vector2) / (
            np.linalg.norm(vector1) * np.linalg.norm(vector2)
        )
        if similarity > 0.2:
            width.append(int(similarity * 10))
            string += "{} {}\n".format(len(width), df.loc[i, "title"])
    G = nx.Graph([(0, i + 1) for i in range(len(width))])
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, width=width)
    return string, plt.gcf()


def translate(text, key):
    return ""


def trend(frame, key):
    return ""


with gr.Blocks(title="WIN", css="footer{visibility: hidden}") as win:
    gr.HTML('<h1 align="center">博览群篇——智能驱动的文献分析可视化工具</h1>')
    with gr.Row():
        with gr.Column(scale=2):
            with gr.Tab(label="文本"):
                text = gr.Textbox(show_label=False, lines=25)
            with gr.Tab(label="表格"):
                frame = gr.Dataframe(show_label=False, headers=[""])
            with gr.Tab(label="图像"):
                image = gr.Plot(show_label=False)
        with gr.Column(scale=1):
            books = ["FOCS", "ICML", "NeurIPS", "SODA", "STOC"]
            years = ["2022", "2021", "2020", "2019", "2018"]
            years += ["2017", "2016", "2015", "2014", "2013"]
            years += ["2012", "2011", "2010", "2009", "2008"]
            years += ["2007", "2006", "2005", "2004", "2003"]
            years += ["2002", "2001", "2000", "1999", "1998"]
            years += ["1997", "1996", "1995", "1994", "1993"]
            years += ["1992", "1991", "1990", "1989", "1988"]
            years += ["1987", "1986", "1985"]
            types = ["title", "author", "abstract"]
            file = gr.File(show_label=False, height=100, file_count="multiple")
            book = gr.Dropdown(show_label=False, multiselect=True, choices=books)
            year = gr.Dropdown(show_label=False, multiselect=True, choices=years)
            type = gr.Dropdown(show_label=False, choices=types, value="title")
            input = gr.Textbox(show_label=False, placeholder="输入")
            key = gr.Textbox(show_label=False, placeholder="密钥", type="password")
            with gr.Row():
                gr.Button(value="文件读取").click(read, [file, input], text)
                gr.Button(value="内容查找").click(
                    find, [book, year, type, input], frame
                )
            with gr.Row():
                gr.Button(value="关系绘制").click(plot, frame, [text, image])
                gr.Button(value="相似推荐").click(
                    recommend, [frame, input], [text, image]
                )
            with gr.Row():
                gr.Button(value="总结翻译").click(translate, [text, key], text)
                gr.Button(value="研究走向").click(trend, [frame, key], text)


if __name__ == "__main__":
    win.launch()
