import type { CertConfig } from "./Types";
import { useConfigSection, SectionWithToggle, Input } from "./UI";

interface Props {
  config: CertConfig;
  onChange: (c: CertConfig) => void;
}

export const Cert = ({ config, onChange }: Props) => {
  const [local, update] = useConfigSection(config, onChange);

  return (
    <div className="space-y-5">
      <SectionWithToggle
        title="Auto Certificate"
        enabled={local.enabled}
        onToggle={(v) => update({ enabled: v })}
      />

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

      <div className="grid grid-cols-2 gap-3">
        <Input
          mono
          label="Cert Path"
          value={local.cert}
          onChange={(v) => update({ cert: v })}
          placeholder=".cache/cert.pem"
          hint="Let's Encrypt certificate destination"
        />
        <Input
          mono
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
