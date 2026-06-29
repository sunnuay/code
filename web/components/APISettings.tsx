import { useState, useEffect } from "react";
import { RefreshCw } from "lucide-react";
import type { APIConfig } from "../App";
import { Card, Input, SaveButton } from "./Primitives";

interface Props {
  config: APIConfig;
  onSave: (c: APIConfig) => void;
  saving: boolean;
  restarting: boolean;
  onRestart: () => void;
}

const APISettings = ({ config, onSave, saving, restarting, onRestart }: Props) => {
  const [local, setLocal] = useState<APIConfig>(config);

  useEffect(() => { setLocal(config); }, [config]);

  return (
    <Card className="p-6">
      <h2 className="text-lg font-semibold text-black mb-6">Web API 设置</h2>

      <div className="space-y-5">
        <Input
          label="API 监听地址"
          value={local.listen}
          onChange={(v) => setLocal({ listen: v })}
          disabled={saving}
        />

        <div className="flex justify-end">
          <SaveButton saving={saving} onClick={() => onSave(local)} label="保存设置" />
        </div>
      </div>

      <hr className="my-6 border-gray-100" />

      <div>
        <h3 className="text-sm font-semibold text-black mb-3">服务管理</h3>
        <button
          onClick={onRestart}
          disabled={restarting}
          className="inline-flex items-center gap-2 px-4 py-2 rounded-md bg-red-500 hover:bg-red-600 disabled:bg-red-300 text-white text-sm font-medium transition-colors"
        >
          <RefreshCw size={14} className={restarting ? "animate-spin" : ""} />
          {restarting ? "重启中..." : "重启服务"}
        </button>
      </div>
    </Card>
  );
};

export default APISettings;
