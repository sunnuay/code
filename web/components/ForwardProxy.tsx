import { useState, useEffect } from "react";
import type { ForwardConfig } from "../App";
import { Card, CardHeader, ToggleRow, Input, SaveButton } from "./ui";

interface Props {
  config: ForwardConfig;
  onSave: (c: ForwardConfig) => void;
  saving: boolean;
}

const ForwardProxy = ({ config, onSave, saving }: Props) => {
  const [local, setLocal] = useState<ForwardConfig>(config);

  useEffect(() => { setLocal(config); }, [config]);

  return (
    <Card className="p-6">
      <CardHeader title="全局设置" status={{ enabled: local.enabled }} />

      <div className="space-y-5">
        <ToggleRow
          label="启用正向代理"
          checked={local.enabled}
          onChange={(v) => setLocal({ ...local, enabled: v })}
          disabled={saving}
        />

        <Input
          label="监听地址"
          value={local.listen}
          onChange={(v) => setLocal({ ...local, listen: v })}
          placeholder=":10001"
          disabled={saving}
        />

        <div className="pt-2 flex justify-end">
          <SaveButton saving={saving} onClick={() => onSave(local)} />
        </div>
      </div>
    </Card>
  );
};

export default ForwardProxy;
