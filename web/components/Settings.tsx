import type { APIConfig, WebConfig, Theme } from "./Types";
import { themes } from "./Types";
import { useConfigSection, SectionHeader, Input } from "./UI";

interface Props {
  config: APIConfig;
  onChange: (c: APIConfig) => void;
  webConfig: WebConfig;
  onWebConfigChange: (patch: Partial<WebConfig>) => void;
}

export const Settings = ({
  config,
  onChange,
  webConfig,
  onWebConfigChange,
}: Props) => {
  const [local, update] = useConfigSection(config, onChange);

  return (
    <div className="space-y-5">
      <SectionHeader title="API Settings" />

      <Input
        mono
        label="Listen Address"
        value={local.listen}
        onChange={(v) => update({ listen: v })}
      />

      <p className="text-ctp-overlay1 text-xs">
        Changes to the listen address require a restart to take effect.
      </p>

      <hr className="border-ctp-surface0" />

      <SectionHeader title="Web UI" />

      <Input
        mono
        label="API URL"
        value={webConfig.apiUrl}
        onChange={(v) => onWebConfigChange({ apiUrl: v })}
      />

      <div>
        <label className="block text-xs font-medium text-ctp-subtext0 mb-1.5 tracking-wide">
          Theme
        </label>
        <div className="flex items-center gap-1">
          {themes.map(({ id, name }) => {
            const active = webConfig.theme === id;
            return (
              <button
                key={id}
                type="button"
                onClick={() => onWebConfigChange({ theme: id as Theme })}
                className={`rounded-full px-3.5 py-2 text-[13px] font-medium transition-all duration-200 ${
                  active
                    ? "bg-ctp-pink text-ctp-base shadow-sm"
                    : "text-ctp-subtext0 hover:text-ctp-text hover:bg-ctp-surface0"
                }`}
              >
                {name}
              </button>
            );
          })}
        </div>
      </div>
    </div>
  );
};
