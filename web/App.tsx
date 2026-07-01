import { useState, useEffect } from "react";
import { type Config, defaultConfig } from "./components/Types";
import { Nav } from "./components/Nav";
import { Content } from "./components/Content";
import { ErrorBar } from "./components/UI";

const API = "http://localhost:10000";

export default function App() {
  const [activeTab, setActiveTab] = useState("forward");
  const [config, setConfig] = useState<Config>(defaultConfig);
  const [loading, setLoading] = useState(true);
  const [saving, setSaving] = useState(false);
  const [saved, setSaved] = useState(false);
  const [restarting, setRestarting] = useState(false);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    fetch(`${API}/api/config`)
      .then((r) => (r.ok ? r.json() : Promise.reject()))
      .then(setConfig)
      .catch(() => {})
      .finally(() => setLoading(false));
  }, []);

  const update = <K extends keyof Config>(key: K, value: Config[K]) =>
    setConfig((prev) => ({ ...prev, [key]: value }));

  const save = async () => {
    setSaving(true);
    setError(null);
    try {
      const res = await fetch(`${API}/api/config`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(config),
      });
      if (!res.ok) throw new Error(`HTTP ${res.status}`);
      setConfig(await res.json());
      setSaved(true);
      setTimeout(() => setSaved(false), 2500);
    } catch (e: unknown) {
      setError(e instanceof Error ? e.message : "Save failed");
    } finally {
      setSaving(false);
    }
  };

  const restart = async () => {
    setRestarting(true);
    setError(null);
    try {
      await fetch(`${API}/api/restart`, { method: "POST" });
    } catch {}
    setTimeout(() => {
      setRestarting(false);
      fetch(`${API}/api/config`)
        .then((r) => r.ok && r.json())
        .then((c) => c && setConfig(c))
        .catch(() => {});
    }, 1500);
  };

  return (
    <div className="bg-ctp-base flex min-h-screen items-start justify-center p-6 pt-20 pb-24">
      <div className="w-full max-w-2xl">
        <div className="bg-ctp-mantle ring-ctp-crust overflow-hidden rounded-2xl shadow-[0_2px_16px_rgba(0,0,0,0.03),0_12px_48px_rgba(0,0,0,0.04)] ring-1">
          <Nav
            activeTab={activeTab}
            onTabChange={setActiveTab}
            onSave={save}
            onRestart={restart}
            saving={saving}
            saved={saved}
            restarting={restarting}
          />
          {error && (
            <div className="px-6 pt-4">
              <ErrorBar message={error} onDismiss={() => setError(null)} />
            </div>
          )}
          <div className="px-6 py-6">
            <Content
              activeTab={activeTab}
              config={config}
              loading={loading}
              onChange={update}
            />
          </div>
        </div>
      </div>
    </div>
  );
}
