import type { ForwardConfig } from "./Types";
import { useConfigSection, SectionHeader, ToggleRow, Input } from "./UI";

interface Props {
  config: ForwardConfig;
  onChange: (c: ForwardConfig) => void;
}

export const Forward = ({ config, onChange }: Props) => {
  const [local, update] = useConfigSection(config, onChange);

  return (
    <div className="space-y-5">
      <div className="flex items-center justify-between">
        <SectionHeader title="Forward Proxy" />
        <ToggleRow
          checked={local.enabled}
          onChange={(v) => update({ enabled: v })}
        />
      </div>

      <Input
        mono
        label="Listen Address"
        value={local.listen}
        onChange={(v) => update({ listen: v })}
        placeholder=":10001"
      />
    </div>
  );
};
