import { useState, useEffect } from "react";
import type { DDNSConfig } from "../App";
import { Card, CardHeader, ToggleRow, Input, NumberInput, SaveButton } from "./ui";

interface Props {
  config: DDNSConfig;
  onSave: (c: DDNSConfig) => void;
  saving: boolean;
}

const DDNS = ({ config, onSave, saving }: Props) => {
  const [local, setLocal] = useState<DDNSConfig>(config);

  useEffect(() => { setLocal(config); }, [config]);

  return (
    <Card className="p-6">
      <CardHeader title="域名配置" status={{ enabled: local.enabled }} />

      <div className="space-y-5">
        <ToggleRow
          label="启用 DDNS"
          checked={local.enabled}
          onChange={(v) => setLocal({ ...local, enabled: v })}
          disabled={saving}
        />

        <Input
          label="域名"
          value={local.domain}
          onChange={(v) => setLocal({ ...local, domain: v })}
          placeholder="example.com"
          disabled={saving}
        />

        <Input
          label="API Token"
          type="password"
          value={local.api_token}
          onChange={(v) => setLocal({ ...local, api_token: v })}
          placeholder="Cloudflare API Token"
          disabled={saving}
        />

        <NumberInput
          label="同步间隔 (秒)"
          value={local.interval}
          onChange={(v) => setLocal({ ...local, interval: v })}
          min={10}
          disabled={saving}
        />

        <div className="pt-2 flex justify-end">
          <SaveButton saving={saving} onClick={() => onSave(local)} />
        </div>
      </div>
    </Card>
  );
};

export default DDNS;
