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
import HeaderBar from "./components/HeaderBar";
import TabContent from "./components/TabContent";

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
  cert: {
    enabled: false,
    cert: ".cache/cert.pem",
    key: ".cache/key.pem",
    api_token: "",
    domain: "",
  },
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
      setError(
        `无法连接到服务器: ${e instanceof Error ? e.message : String(e)}`,
      );
    } finally {
      setLoading(false);
    }
  }, []);

  useEffect(() => {
    fetchConfig();
  }, [fetchConfig]);

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
    try {
      await fetch(`${API_BASE}/api/restart`, { method: "POST" });
    } catch {}
    setTimeout(() => {
      setRestarting(false);
      setMessage(null);
      fetchConfig();
    }, 1000);
  };

  const update =
    <K extends keyof Config>(key: K) =>
    (val: Config[K]) => {
      void saveConfig({ ...config, [key]: val });
    };

  const currentName = menuItems.find((i) => i.id === activeTab)?.name ?? "";

  return (
    <div className="flex h-screen bg-white font-sans text-black antialiased">
      <Sidebar
        menuItems={menuItems}
        activeTab={activeTab}
        onTabChange={setActiveTab}
      />
      <main className="flex h-screen flex-1 flex-col overflow-hidden">
        <HeaderBar title={currentName} error={error} message={message} />
        <div className="flex-1 overflow-auto p-6">
          <div className="mx-auto max-w-3xl">
            <TabContent
              activeTab={activeTab}
              config={config}
              loading={loading}
              saving={saving}
              restarting={restarting}
              onSave={update}
              onRestart={handleRestart}
            />
          </div>
        </div>
      </main>
    </div>
  );
};

export default App;
