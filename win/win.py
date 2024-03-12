# gradio==3.50.2
# networkx
# pymupdf
# openai


import gradio as gr
import matplotlib.pyplot as plt
import pandas as pd
import networkx as nx
import fitz
import openai
import random


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
            list.append(pd.read_csv(f"data/{b}/{b}_{y}.csv"))
    df = pd.concat(list)
    df = df[df[type].str.contains(input, case=False)]
    df = df.drop(columns="abstract")
    return df


def plot(frame):
    plt.clf()
    n, m = 10, 5
    width = [random.randint(1, m) for _ in range(m)]
    G = nx.gnm_random_graph(n, m)
    pos = nx.circular_layout(G)
    nx.draw(G, pos, with_labels=True, width=width)
    return "", plt.gcf()


def recommend(frame):
    plt.clf()
    m = 9
    width = [random.randint(1, m) for _ in range(m)]
    G = nx.Graph([(0, i + 1) for i in range(m)])
    pos = nx.spring_layout(G)
    nx.draw(G, pos, with_labels=True, width=width)
    return "", plt.gcf()


def translate(text, key):
    try:
        system = "You are a helpful assistant."
        user = "Translate English to Chinese: " + text
        client = openai.OpenAI(api_key=key)
        completion = client.chat.completions.create(
            model="gpt-3.5-turbo",
            messages=[
                {"role": "system", "content": system},
                {"role": "user", "content": user},
            ],
        )
        return completion.choices[0].message
    except Exception as e:
        return e


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
            years = ["2013", "2014", "2015", "2016", "2017"]
            years += ["2018", "2019", "2020", "2021", "2022"]
            types = ["ee", "title", "author", "abstract"]
            file = gr.File(show_label=False, height=100, file_count="multiple")
            book = gr.Dropdown(show_label=False, multiselect=True, choices=books)
            year = gr.Dropdown(show_label=False, multiselect=True, choices=years)
            type = gr.Dropdown(show_label=False, choices=types, value="ee")
            input = gr.Textbox(show_label=False, placeholder="输入")
            key = gr.Textbox(show_label=False, placeholder="密钥", type="password")
            with gr.Row():
                gr.Button(value="文件读取").click(read, [file, input], text)
                gr.Button(value="内容查找").click(find, [book, year, type, input], frame)
            with gr.Row():
                gr.Button(value="关系绘制").click(plot, frame, [text, image])
                gr.Button(value="相似推荐").click(recommend, frame, [text, image])
            with gr.Row():
                gr.Button(value="总结翻译").click(translate, [text, key], text)
                gr.Button(value="研究走向").click(trend, [frame, key], text)


if __name__ == "__main__":
    win.launch()
