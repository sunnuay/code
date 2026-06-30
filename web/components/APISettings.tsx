import { useState, useEffect } from "react";
import type { APIConfig } from "../App";
import { SectionHeader, MonoInput } from "./Primitives";

interface Props {
  config: APIConfig;
  onChange: (c: APIConfig) => void;
}

const APISettings = ({ config, onChange }: Props) => {
  const [local, setLocal] = useState<APIConfig>(config);

  useEffect(() => {
    setLocal(config);
  }, [config]);

  const update = (patch: Partial<APIConfig>) => {
    const next = { ...local, ...patch };
    setLocal(next);
    onChange(next);
  };

  return (
    <div className="space-y-5">
      <SectionHeader title="API Settings" />

      <MonoInput
        label="Listen Address"
        value={local.listen}
        onChange={(v) => update({ listen: v })}
        placeholder=":10000"
      />

      <p className="text-xs text-[#A3A3A3]">
        Changes to the listen address require a restart to take effect.
      </p>
    </div>
  );
};

export default APISettings;
