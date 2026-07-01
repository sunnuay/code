import type { ForwardConfig } from "./Types";
import { useConfigSection, SectionWithToggle, Input } from "./UI";

interface Props {
  config: ForwardConfig;
  onChange: (c: ForwardConfig) => void;
}

export const Forward = ({ config, onChange }: Props) => {
  const [local, update] = useConfigSection(config, onChange);

  return (
    <div className="space-y-5">
      <SectionWithToggle
        title="Forward Proxy"
        enabled={local.enabled}
        onToggle={(v) => update({ enabled: v })}
      />

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
