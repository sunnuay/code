from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler


def _run_torch() -> str:
    import torch

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
        preds = model(X_test).argmax(dim=1)
        acc = (preds == y_test).float().mean().item()

    return f"torch: {acc:.4f}"


def _run_sklearn() -> str:
    from sklearn.neural_network import MLPClassifier

    X, y = load_iris(return_X_y=True)
    X_train, X_test, y_train, y_test = train_test_split(
        X, y, train_size=0.5, random_state=0
    )

    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    X_test = scaler.transform(X_test)

    mlp = MLPClassifier(hidden_layer_sizes=10, max_iter=2000)
    mlp.fit(X_train, y_train)

    return f"sklearn: {mlp.score(X_test, y_test):.4f}"


def run(method: str) -> str:
    if method == "torch":
        return _run_torch()
    elif method == "sklearn":
        return _run_sklearn()
    else:
        return f"unknown method: {method}"
