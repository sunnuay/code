import type { Config, WebConfig } from "./Types";
import { Forward } from "./Forward";
import { Reverse } from "./Reverse";
import { DDNS } from "./DDNS";
import { Cert } from "./Cert";
import { Settings } from "./Settings";

interface Props {
  activeTab: string;
  config: Config;
  loading: boolean;
  onChange: <K extends keyof Config>(key: K, value: Config[K]) => void;
  webConfig: WebConfig;
  onWebConfigChange: (patch: Partial<WebConfig>) => void;
}

export const Content = ({
  activeTab,
  config,
  loading,
  onChange,
  webConfig,
  onWebConfigChange,
}: Props) => {
  if (loading) {
    return (
      <div className="flex h-64 items-center justify-center">
        <div className="flex flex-col items-center gap-4">
          <div className="flex items-center gap-1.5">
            {[0, 1, 2].map((i) => (
              <div
                key={i}
                className="bg-ctp-overlay1 h-2 w-2 animate-pulse rounded-full"
                style={{ animationDelay: `${i * 150}ms` }}
              />
            ))}
          </div>
          <span className="text-ctp-overlay1 text-sm">
            Loading configuration...
          </span>
        </div>
      </div>
    );
  }

  const on =
    <K extends keyof Config>(key: K) =>
    (c: Config[K]) =>
      onChange(key, c);

  switch (activeTab) {
    case "forward":
      return <Forward config={config.forward} onChange={on("forward")} />;
    case "reverse":
      return <Reverse config={config.reverse} onChange={on("reverse")} />;
    case "ddns":
      return <DDNS config={config.ddns} onChange={on("ddns")} />;
    case "cert":
      return <Cert config={config.cert} onChange={on("cert")} />;
    case "settings":
      return (
        <Settings
          config={config.api}
          onChange={on("api")}
          webConfig={webConfig}
          onWebConfigChange={onWebConfigChange}
        />
      );
    default:
      return null;
  }
};
