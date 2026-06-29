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
  tls: boolean;
  cert: string;
  key: string;
  routes: RouteConfig[];
}

export interface DDNSConfig {
  enabled: boolean;
  interval: number;
  api_token: string;
  domain: string;
}

export interface CertConfig {
  enabled: boolean;
  cert: string;
  key: string;
  api_token: string;
  domain: string;
}

export interface Config {
  api: APIConfig;
  forward: ForwardConfig;
  reverse: ReverseConfig;
  ddns: DDNSConfig;
  cert: CertConfig;
}

const defaultConfig: Config = {
  api: { listen: ":10000" },
  forward: { enabled: false, listen: ":10001" },
  reverse: {
    enabled: false,
    listen: ":9999",
    tls: false,
    cert: ".cache/cert.pem",
    key: ".cache/key.pem",
    routes: [{ path: "/server/", target: "http://127.0.0.1:8080" }],
  },
  ddns: { enabled: false, interval: 600, api_token: "", domain: "" },
  cert: { enabled: false, cert: ".cache/cert.pem", key: ".cache/key.pem", api_token: "", domain: "" },
};

const API_BASE = "http://localhost:10000";

const menuItems: MenuItem[] = [
  { id: "forward", name: "正向代理", icon: ShieldCheck },
  { id: "reverse", name: "反向代理", icon: ArrowRightLeft },
  { id: "ddns", name: "动态域名", icon: Globe },
  { id: "cert", name: "自动证书", icon: Lock },
  { id: "settings", name: "系统设置", icon: Settings },
];

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
      setConfig(await res.json());
    } catch (e: unknown) {
      setError(`无法连接到服务器: ${e instanceof Error ? e.message : String(e)}`);
    } finally {
      setLoading(false);
    }
  }, []);

  useEffect(() => { fetchConfig(); }, [fetchConfig]);

  const saveConfig = useCallback(async (updated: Config) => {
    setSaving(true);
    setError(null);
    setMessage(null);
    try {
      const res = await fetch(`${API_BASE}/api/config`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(updated),
      });
      if (!res.ok) throw new Error(`HTTP ${res.status}`);
      setConfig(await res.json());
      setMessage("配置已保存 (需重启服务生效)");
      setTimeout(() => setMessage(null), 4000);
    } catch (e: unknown) {
      setError(`保存失败: ${e instanceof Error ? e.message : String(e)}`);
    } finally {
      setSaving(false);
    }
  }, []);

  const handleRestart = async () => {
    setRestarting(true);
    setMessage("正在重启服务...");
    try { await fetch(`${API_BASE}/api/restart`, { method: "POST" }); } catch {}
    setTimeout(() => {
      setRestarting(false);
      setMessage(null);
      fetchConfig();
    }, 1000);
  };

  const update = <K extends keyof Config>(key: K) => (val: Config[K]) =>
    saveConfig({ ...config, [key]: val });

  const renderContent = () => {
    if (loading) {
      return (
        <div className="flex items-center justify-center h-64">
          <div className="flex flex-col items-center gap-3 text-gray-400">
            <div className="w-6 h-6 border-2 border-black border-t-transparent rounded-full animate-spin" />
            <span className="text-sm">加载配置中...</span>
          </div>
        </div>
      );
    }

    const tab = activeTab;
    if (tab === "forward") return <ForwardProxy config={config.forward} onSave={update("forward")} saving={saving} />;
    if (tab === "reverse") return <ReverseProxy config={config.reverse} onSave={update("reverse")} saving={saving} />;
    if (tab === "ddns") return <DDNS config={config.ddns} onSave={update("ddns")} saving={saving} />;
    if (tab === "cert") return <CertManagement config={config.cert} onSave={update("cert")} saving={saving} />;
    if (tab === "settings") return <APISettings config={config.api} onSave={update("api")} saving={saving} restarting={restarting} onRestart={handleRestart} />;
    return null;
  };

  const currentName = menuItems.find((i) => i.id === activeTab)?.name;

  return (
    <div className="flex h-screen bg-white font-sans text-black antialiased">
      <Sidebar menuItems={menuItems} activeTab={activeTab} onTabChange={setActiveTab} />

      <main className="flex-1 flex flex-col h-screen overflow-hidden">
        <header className="h-14 bg-white border-b border-gray-100 flex items-center px-6 flex-shrink-0 gap-4">
          <h2 className="text-sm font-semibold text-black">{currentName}</h2>
          <div className="flex-1" />
          {error && (
            <span className="text-xs text-red-600 bg-red-50 px-2.5 py-1 rounded-full">{error}</span>
          )}
          {message && (
            <span className="text-xs text-gray-600 bg-gray-50 px-2.5 py-1 rounded-full border border-gray-200">{message}</span>
          )}
        </header>

        <div className="flex-1 overflow-auto p-6">
          <div className="max-w-3xl mx-auto">{renderContent()}</div>
        </div>
      </main>
    </div>
  );
};

export default App;
