import { createRoot } from "react-dom/client";

function App() {
	document.title = "coding";
	document.documentElement.lang = "en";
	return (
		<div>
			<h1>hello</h1>
		</div>
	);
}

createRoot(document.getElementById("root")!).render(<App />);
