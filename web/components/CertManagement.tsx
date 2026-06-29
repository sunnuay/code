import { useState, useEffect } from "react";
import type { CertConfig } from "../App";
import { Card, CardHeader, ToggleRow, Input, SaveButton } from "./ui";

interface Props {
  config: CertConfig;
  onSave: (c: CertConfig) => void;
  saving: boolean;
}

const CertManagement = ({ config, onSave, saving }: Props) => {
  const [local, setLocal] = useState<CertConfig>(config);

  useEffect(() => { setLocal(config); }, [config]);

  return (
    <Card className="p-6">
      <CardHeader title="证书自动化配置" status={{ enabled: local.enabled }} />

      <div className="space-y-5">
        <ToggleRow
          label="启用自动证书"
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

        <Input
          label="证书路径"
          value={local.cert}
          onChange={(v) => setLocal({ ...local, cert: v })}
          placeholder=".cache/cert.pem"
          hint="Let's Encrypt 签发的证书保存路径"
          disabled={saving}
        />

        <Input
          label="密钥路径"
          value={local.key}
          onChange={(v) => setLocal({ ...local, key: v })}
          placeholder=".cache/key.pem"
          hint="证书私钥保存路径"
          disabled={saving}
        />

        <div className="pt-2 flex justify-end">
          <SaveButton saving={saving} onClick={() => onSave(local)} />
        </div>
      </div>
    </Card>
  );
};

export default CertManagement;
