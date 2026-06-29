import type { Config } from "../App";
import ForwardProxy from "./ForwardProxy";
import ReverseProxy from "./ReverseProxy";
import DDNS from "./DDNS";
import CertManagement from "./CertManagement";
import APISettings from "./APISettings";

interface TabContentProps {
  activeTab: string;
  config: Config;
  loading: boolean;
  saving: boolean;
  restarting: boolean;
  onSave: <K extends keyof Config>(key: K) => (val: Config[K]) => void;
  onRestart: () => void;
}

const TabContent = ({
  activeTab,
  config,
  loading,
  saving,
  restarting,
  onSave,
  onRestart,
}: TabContentProps) => {
  if (loading) {
    return (
      <div className="flex h-64 items-center justify-center">
        <div className="flex flex-col items-center gap-3 text-gray-400">
          <div className="h-6 w-6 animate-spin rounded-full border-2 border-black border-t-transparent" />
          <span className="text-sm">加载配置中...</span>
        </div>
      </div>
    );
  }

  switch (activeTab) {
    case "forward":
      return (
        <ForwardProxy
          config={config.forward}
          onSave={onSave("forward")}
          saving={saving}
        />
      );
    case "reverse":
      return (
        <ReverseProxy
          config={config.reverse}
          onSave={onSave("reverse")}
          saving={saving}
        />
      );
    case "ddns":
      return (
        <DDNS config={config.ddns} onSave={onSave("ddns")} saving={saving} />
      );
    case "cert":
      return (
        <CertManagement
          config={config.cert}
          onSave={onSave("cert")}
          saving={saving}
        />
      );
    case "settings":
      return (
        <APISettings
          config={config.api}
          onSave={onSave("api")}
          saving={saving}
          restarting={restarting}
          onRestart={onRestart}
        />
      );
    default:
      return null;
  }
};

export default TabContent;
