import type { APIConfig } from "./Types";
import { useConfigSection, SectionHeader, Input } from "./UI";

interface Props {
  config: APIConfig;
  onChange: (c: APIConfig) => void;
}

export const Settings = ({ config, onChange }: Props) => {
  const [local, update] = useConfigSection(config, onChange);

  return (
    <div className="space-y-5">
      <SectionHeader title="API Settings" />

      <Input
        mono
        label="Listen Address"
        value={local.listen}
        onChange={(v) => update({ listen: v })}
        placeholder=":10000"
      />

      <p className="text-ctp-overlay1 text-xs">
        Changes to the listen address require a restart to take effect.
      </p>
    </div>
  );
};
