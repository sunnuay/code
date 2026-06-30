import { useState, useEffect } from "react";
import type { DDNSConfig } from "../App";
import {
  SectionHeader,
  ToggleRow,
  MonoInput,
  Input,
  NumberInput,
} from "./Primitives";

interface Props {
  config: DDNSConfig;
  onChange: (c: DDNSConfig) => void;
}

const DDNS = ({ config, onChange }: Props) => {
  const [local, setLocal] = useState<DDNSConfig>(config);

  useEffect(() => {
    setLocal(config);
  }, [config]);

  const update = (patch: Partial<DDNSConfig>) => {
    const next = { ...local, ...patch };
    setLocal(next);
    onChange(next);
  };

  return (
    <div className="space-y-5">
      <div className="flex items-center justify-between">
        <SectionHeader title="Dynamic DNS" />
        <ToggleRow
          label=""
          checked={local.enabled}
          onChange={(v) => update({ enabled: v })}
        />
      </div>

      <MonoInput
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

export default DDNS;
