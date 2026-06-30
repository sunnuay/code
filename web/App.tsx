import { useState, useEffect, useCallback } from "react";
import TabContent from "./components/TabContent";
import { SaveButton, RestartButton, ErrorBar } from "./components/Primitives";

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

const menuItems = [
  { id: "forward", name: "Forward" },
  { id: "reverse", name: "Reverse" },
  { id: "ddns", name: "DDNS" },
  { id: "cert", name: "Cert" },
  { id: "settings", name: "Settings" },
];

const App = () => {
  const [activeTab, setActiveTab] = useState("forward");
  const [config, setConfig] = useState<Config>(defaultConfig);
  const [loading, setLoading] = useState(true);
  const [saving, setSaving] = useState(false);
  const [saved, setSaved] = useState(false);
  const [restarting, setRestarting] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const fetchConfig = useCallback(async () => {
    setLoading(true);
    try {
      const res = await fetch(`${API_BASE}/api/config`);
      if (!res.ok) throw new Error(`HTTP ${res.status}`);
      setConfig(await res.json());
    } catch {
      // Silently fail
    } finally {
      setLoading(false);
    }
  }, []);

  useEffect(() => {
    fetchConfig();
  }, [fetchConfig]);

  const updateSection = useCallback(
    <K extends keyof Config>(key: K, value: Config[K]) => {
      setConfig((prev) => ({ ...prev, [key]: value }));
      setSaved(false);
    },
    [],
  );

  const handleSaveAll = useCallback(async () => {
    setSaving(true);
    setError(null);
    setSaved(false);
    try {
      const res = await fetch(`${API_BASE}/api/config`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(config),
      });
      if (!res.ok) throw new Error(`HTTP ${res.status}`);
      const fresh = await res.json();
      setConfig(fresh);
      setSaved(true);
      setTimeout(() => setSaved(false), 2500);
    } catch (e: unknown) {
      setError(e instanceof Error ? e.message : "Failed to save");
    } finally {
      setSaving(false);
    }
  }, [config]);

  const handleRestart = useCallback(async () => {
    setRestarting(true);
    setError(null);
    try {
      await fetch(`${API_BASE}/api/restart`, { method: "POST" });
    } catch {
      // Restart endpoint may not respond before the service dies
    }
    setTimeout(() => {
      setRestarting(false);
      fetchConfig();
    }, 1500);
  }, [fetchConfig]);

  return (
    <div
      className="min-h-screen bg-[#F5F4F1] flex items-start justify-center p-6 pt-20 pb-24"
      style={{
        backgroundImage:
          "radial-gradient(circle, #E6E4DE 1px, transparent 1px)",
        backgroundSize: "28px 28px",
      }}
    >
      <div className="w-full max-w-2xl">
        {/* Main card */}
        <div className="bg-white rounded-2xl shadow-[0_2px_16px_rgba(0,0,0,0.03),0_12px_48px_rgba(0,0,0,0.04)] ring-1 ring-black/[0.03] overflow-hidden">
          {/* Header: nav pills + actions */}
          <div className="px-5 pt-4 pb-3 flex items-center justify-between border-b border-[#F0EFEB]">
            <div className="flex items-center gap-1">
              {menuItems.map((item) => {
                const isActive = activeTab === item.id;
                return (
                  <button
                    key={item.id}
                    onClick={() => setActiveTab(item.id)}
                    className={`px-3.5 py-2 rounded-full text-[13px] font-medium transition-all duration-200 ${
                      isActive
                        ? "bg-[#1E1E3F] text-white shadow-sm"
                        : "text-[#6B6B6B] hover:text-[#171717] hover:bg-[#F5F4F1]"
                    }`}
                  >
                    {item.name}
                  </button>
                );
              })}
            </div>
            <div className="flex items-center gap-2">
              <RestartButton
                onClick={handleRestart}
                restarting={restarting}
                label="Restart"
              />
              <SaveButton
                onClick={handleSaveAll}
                saving={saving}
                saved={saved}
                label="Save All"
              />
            </div>
          </div>

          {/* Global error */}
          {error && (
            <div className="px-6 pt-4">
              <ErrorBar message={error} onDismiss={() => setError(null)} />
            </div>
          )}

          {/* Content */}
          <div className="px-6 py-6">
            <TabContent
              activeTab={activeTab}
              config={config}
              loading={loading}
              onChange={updateSection}
            />
          </div>
        </div>
      </div>
    </div>
  );
};

export default App;
