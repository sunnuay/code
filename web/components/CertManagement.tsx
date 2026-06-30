import { useState, useEffect } from "react";
import type { CertConfig } from "../App";
import {
  SectionHeader,
  ToggleRow,
  MonoInput,
  Input,
} from "./Primitives";

interface Props {
  config: CertConfig;
  onChange: (c: CertConfig) => void;
}

const CertManagement = ({ config, onChange }: Props) => {
  const [local, setLocal] = useState<CertConfig>(config);

  useEffect(() => {
    setLocal(config);
  }, [config]);

  const update = (patch: Partial<CertConfig>) => {
    const next = { ...local, ...patch };
    setLocal(next);
    onChange(next);
  };

  return (
    <div className="space-y-5">
      <div className="flex items-center justify-between">
        <SectionHeader title="Auto Certificate" />
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

      <div className="grid grid-cols-2 gap-3">
        <MonoInput
          label="Cert Path"
          value={local.cert}
          onChange={(v) => update({ cert: v })}
          placeholder=".cache/cert.pem"
          hint="Let's Encrypt certificate destination"
        />
        <MonoInput
          label="Key Path"
          value={local.key}
          onChange={(v) => update({ key: v })}
          placeholder=".cache/key.pem"
          hint="Private key destination"
        />
      </div>
    </div>
  );
};

export default CertManagement;
