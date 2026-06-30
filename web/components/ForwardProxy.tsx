import { useState, useEffect } from "react";
import type { ForwardConfig } from "../App";
import { SectionHeader, ToggleRow, MonoInput } from "./Primitives";

interface Props {
  config: ForwardConfig;
  onChange: (c: ForwardConfig) => void;
}

const ForwardProxy = ({ config, onChange }: Props) => {
  const [local, setLocal] = useState<ForwardConfig>(config);

  useEffect(() => {
    setLocal(config);
  }, [config]);

  const update = (patch: Partial<ForwardConfig>) => {
    const next = { ...local, ...patch };
    setLocal(next);
    onChange(next);
  };

  return (
    <div className="space-y-5">
      <div className="flex items-center justify-between">
        <SectionHeader title="Forward Proxy" />
        <ToggleRow
          label=""
          checked={local.enabled}
          onChange={(v) => update({ enabled: v })}
        />
      </div>

      <MonoInput
        label="Listen Address"
        value={local.listen}
        onChange={(v) => update({ listen: v })}
        placeholder=":10001"
      />
    </div>
  );
};

export default ForwardProxy;
