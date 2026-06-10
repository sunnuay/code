import { useState, useEffect, useCallback } from "react";
import {
	ShieldCheck,
	ArrowRightLeft,
	Globe,
	Lock,
	Settings,
} from "lucide-react";
import Sidebar from "./components/Sidebar";
import type { MenuItem } from "./components/Sidebar";
import ForwardProxy from "./components/ForwardProxy";
import ReverseProxy from "./components/ReverseProxy";
import DDNS from "./components/DDNS";
import CertManagement from "./components/CertManagement";
import APISettings from "./components/APISettings";

// ---- shared config types (match Go structs) ----

export interface APIConfig {
	listen: string;
}

export interface ForwardConfig {
	enabled: boolean;
	listen: string;
}

export interface RouteConfig {
	path: string;
	target: string;
}

export interface ReverseConfig {
	enabled: boolean;
	listen: string;
	routes: RouteConfig[];
}

export interface DDNSConfig {
	enabled: boolean;
	interval: number;
	api_token: string;
	zone_id: string;
	domain: string;
}

export interface CertConfig {
	enabled: boolean;
	email: string;
	cache_dir: string;
	api_token: string;
	zone_id: string;
	domain: string;
}

export interface Config {
	api: APIConfig;
	forward: ForwardConfig;
	reverse: ReverseConfig;
	ddns: DDNSConfig;
	cert: CertConfig;
}

// ---- defaults (used before first fetch) ----

const defaultConfig: Config = {
	api: { listen: ":9999" },
	forward: { enabled: false, listen: ":10000" },
	reverse: { enabled: false, listen: ":10001", routes: [{ path: "/api/", target: "http://127.0.0.1:8080" }] },
	ddns: { enabled: false, interval: 600, api_token: "", zone_id: "", domain: "" },
	cert: { enabled: false, email: "", cache_dir: "./cert", api_token: "", zone_id: "", domain: "" },
};

const API_BASE = "http://localhost:9999";

// ---- menu ----

const menuItems: MenuItem[] = [
	{ id: "forward", name: "正向代理", icon: ShieldCheck },
	{ id: "reverse", name: "反向代理", icon: ArrowRightLeft },
	{ id: "ddns", name: "动态域名", icon: Globe },
	{ id: "cert", name: "自动证书", icon: Lock },
	{ id: "settings", name: "系统设置", icon: Settings },
];

// ---- App ----

const App = () => {
	const [activeTab, setActiveTab] = useState("forward");
	const [config, setConfig] = useState<Config>(defaultConfig);
	const [loading, setLoading] = useState(true);
	const [saving, setSaving] = useState(false);
	const [error, setError] = useState<string | null>(null);
	const [message, setMessage] = useState<string | null>(null);
	const [restarting, setRestarting] = useState(false);

	const fetchConfig = useCallback(async () => {
		setLoading(true);
		setError(null);
		try {
			const res = await fetch(`${API_BASE}/api/config`);
			if (!res.ok) throw new Error(`HTTP ${res.status}`);
			const data: Config = await res.json();
			setConfig(data);
		} catch (e: unknown) {
			const msg = e instanceof Error ? e.message : String(e);
			setError(`无法连接到服务器: ${msg}`);
		} finally {
			setLoading(false);
		}
	}, []);

	useEffect(() => {
		fetchConfig();
	}, [fetchConfig]);

	const saveConfig = useCallback(
		async (updated: Config) => {
			setSaving(true);
			setError(null);
			setMessage(null);
			try {
				const res = await fetch(`${API_BASE}/api/config`, {
					method: "PUT",
					headers: { "Content-Type": "application/json" },
					body: JSON.stringify(updated),
				});
				if (!res.ok) throw new Error(`HTTP ${res.status}`);
				const data: Config = await res.json();
				setConfig(data);
				setMessage("配置已保存 (需重启服务生效)");
				setTimeout(() => setMessage(null), 4000);
			} catch (e: unknown) {
				const msg = e instanceof Error ? e.message : String(e);
				setError(`保存失败: ${msg}`);
			} finally {
				setSaving(false);
			}
		},
		[],
	);

	const handleRestart = async () => {
		setRestarting(true);
		setMessage("正在重启服务...");
		try {
			await fetch(`${API_BASE}/api/restart`, { method: "POST" });
		} catch {
		}
		setTimeout(() => {
			setRestarting(false);
			setMessage(null);
			fetchConfig();
		}, 1000);
	};

	// per-section update helpers
	const updateForward = (f: ForwardConfig) =>
		saveConfig({ ...config, forward: f });
	const updateReverse = (r: ReverseConfig) =>
		saveConfig({ ...config, reverse: r });
	const updateDDNS = (d: DDNSConfig) =>
		saveConfig({ ...config, ddns: d });
	const updateCert = (c: CertConfig) =>
		saveConfig({ ...config, cert: c });
	const updateAPI = (w: APIConfig) =>
		saveConfig({ ...config, api: w });

	const renderContent = () => {
		if (loading) {
			return (
				<div className="flex items-center justify-center h-64">
					<div className="flex flex-col items-center gap-3 text-gray-500">
						<div className="w-8 h-8 border-2 border-blue-500 border-t-transparent rounded-full animate-spin" />
						<span>加载配置中...</span>
					</div>
				</div>
			);
		}

		switch (activeTab) {
			case "forward":
				return (
					<ForwardProxy
						config={config.forward}
						onSave={updateForward}
						saving={saving}
					/>
				);
			case "reverse":
				return (
					<ReverseProxy
						config={config.reverse}
						onSave={updateReverse}
						saving={saving}
					/>
				);
			case "ddns":
				return (
					<DDNS config={config.ddns} onSave={updateDDNS} saving={saving} />
				);
			case "cert":
				return (
					<CertManagement
						config={config.cert}
						onSave={updateCert}
						saving={saving}
					/>
				);
			case "settings":
				return (
					<APISettings
						config={config.api}
						onSave={updateAPI}
						saving={saving}
						restarting={restarting}
						onRestart={handleRestart}
					/>
				);
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
				<header className="h-16 bg-white border-b border-gray-200 flex items-center px-8 flex-shrink-0 gap-4">
					<h2 className="text-xl font-semibold text-gray-800">
						{menuItems.find((i) => i.id === activeTab)?.name}
					</h2>
					{error && (
						<span className="text-sm text-red-600 bg-red-50 px-3 py-1 rounded-full">
							{error}
						</span>
					)}
					{message && (
						<span className="text-sm text-green-600 bg-green-50 px-3 py-1 rounded-full">
							{message}
						</span>
					)}
				</header>

				<div className="flex-1 overflow-auto p-8">
					<div className="max-w-5xl mx-auto">{renderContent()}</div>
				</div>
			</main>
		</div>
	);
};

export default App;
