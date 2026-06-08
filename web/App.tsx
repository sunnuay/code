import { useState } from "react";
import {
	ShieldCheck,
	ArrowRightLeft,
	Globe,
	Lock,
} from "lucide-react";
import Sidebar from "./components/Sidebar";
import type { MenuItem } from "./components/Sidebar";
import ForwardProxy from "./components/ForwardProxy";
import ReverseProxy from "./components/ReverseProxy";
import DDNS from "./components/DDNS";
import CertManagement from "./components/CertManagement";

const menuItems: MenuItem[] = [
	{ id: "forward", name: "正向代理", icon: ShieldCheck },
	{ id: "reverse", name: "反向代理", icon: ArrowRightLeft },
	{ id: "ddns", name: "动态域名", icon: Globe },
	{ id: "cert", name: "自动证书", icon: Lock },
];

const App = () => {
	const [activeTab, setActiveTab] = useState("forward");

	const renderContent = () => {
		switch (activeTab) {
			case "forward":
				return <ForwardProxy />;
			case "reverse":
				return <ReverseProxy />;
			case "ddns":
				return <DDNS />;
			case "cert":
				return <CertManagement />;
			default:
				return null;
		}
	};

	return (
		<div className="flex h-screen bg-[#F8FAFC] font-sans text-gray-900">
			<Sidebar
				menuItems={menuItems}
				activeTab={activeTab}
				onTabChange={setActiveTab}
			/>

			<main className="flex-1 flex flex-col h-screen overflow-hidden">
				<header className="h-16 bg-white border-b border-gray-200 flex items-center px-8 flex-shrink-0">
					<h2 className="text-xl font-semibold text-gray-800">
						{menuItems.find((i) => i.id === activeTab)?.name}
					</h2>
				</header>

				<div className="flex-1 overflow-auto p-8">
					<div className="max-w-5xl mx-auto">{renderContent()}</div>
				</div>
			</main>
		</div>
	);
};

export default App;
