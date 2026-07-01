import type { DDNSConfig } from "./Types";
import {
  useConfigSection,
  SectionHeader,
  ToggleRow,
  Input,
  NumberInput,
} from "./UI";

interface Props {
  config: DDNSConfig;
  onChange: (c: DDNSConfig) => void;
}

export const DDNS = ({ config, onChange }: Props) => {
  const [local, update] = useConfigSection(config, onChange);

  return (
    <div className="space-y-5">
      <div className="flex items-center justify-between">
        <SectionHeader title="Dynamic DNS" />
        <ToggleRow
          checked={local.enabled}
          onChange={(v) => update({ enabled: v })}
        />
      </div>

      <Input
        mono
        label="Domain"
        value={local.domain}
        onChange={(v) => update({ domain: v })}
        placeholder="example.com"
      />

      <Input
        label="API Token"
        type="password"
        value={local.api_token}
        onChange={(v) => update({ api_token: v })}
        placeholder="Cloudflare API Token"
      />

      <NumberInput
        label="Sync Interval (seconds)"
        value={local.interval}
        onChange={(v) => update({ interval: v })}
        min={10}
      />
    </div>
  );
};
