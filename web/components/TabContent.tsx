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
  onChange: <K extends keyof Config>(key: K, value: Config[K]) => void;
}

const TabContent = ({
  activeTab,
  config,
  loading,
  onChange,
}: TabContentProps) => {
  if (loading) {
    return (
      <div className="flex h-64 items-center justify-center">
        <div className="flex flex-col items-center gap-4">
          <div className="flex items-center gap-1.5">
            {[0, 1, 2].map((i) => (
              <div
                key={i}
                className="h-2 w-2 rounded-full bg-ctp-overlay1 animate-pulse"
                style={{ animationDelay: `${i * 150}ms` }}
              />
            ))}
          </div>
          <span className="text-sm text-ctp-overlay1">Loading configuration...</span>
        </div>
      </div>
    );
  }

  switch (activeTab) {
    case "forward":
      return (
        <ForwardProxy
          config={config.forward}
          onChange={(c) => onChange("forward", c)}
        />
      );
    case "reverse":
      return (
        <ReverseProxy
          config={config.reverse}
          onChange={(c) => onChange("reverse", c)}
        />
      );
    case "ddns":
      return (
        <DDNS
          config={config.ddns}
          onChange={(c) => onChange("ddns", c)}
        />
      );
    case "cert":
      return (
        <CertManagement
          config={config.cert}
          onChange={(c) => onChange("cert", c)}
        />
      );
    case "settings":
      return (
        <APISettings
          config={config.api}
          onChange={(c) => onChange("api", c)}
        />
      );
    default:
      return null;
  }
};

export default TabContent;
