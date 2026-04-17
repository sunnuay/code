import torch
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler


def run():
    X, y = load_iris(return_X_y=True)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, train_size=0.5, random_state=0
    )

    scaler = StandardScaler()
    X_train = torch.FloatTensor(scaler.fit_transform(X_train))
    X_test = torch.FloatTensor(scaler.transform(X_test))
    y_train = torch.LongTensor(y_train)
    y_test = torch.LongTensor(y_test)

    model = torch.nn.Sequential(
        torch.nn.Linear(4, 10),
        torch.nn.ReLU(),
        torch.nn.Linear(10, 3),
    )

    criterion = torch.nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.01)

    for _ in range(100):
        optimizer.zero_grad()
        output = model(X_train)
        loss = criterion(output, y_train)
        loss.backward()
        optimizer.step()

    with torch.no_grad():
        preds = torch.argmax(model(X_test), dim=1)
        acc = (preds == y_test).float().mean().item()
        print(f"mlp_torch: {acc:.4f}")
