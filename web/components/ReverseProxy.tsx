import { useState, useEffect } from "react";
import { Plus, Trash2 } from "lucide-react";
import type { ReverseConfig, RouteConfig } from "../App";
import { Card, CardHeader, ToggleRow, Input, SaveButton } from "./Primitives";

interface Props {
  config: ReverseConfig;
  onSave: (c: ReverseConfig) => void;
  saving: boolean;
}

const ReverseProxy = ({ config, onSave, saving }: Props) => {
  const [local, setLocal] = useState<ReverseConfig>(config);
  const [newPath, setNewPath] = useState("");
  const [newTarget, setNewTarget] = useState("");

  useEffect(() => { setLocal(config); }, [config]);

  const addRoute = () => {
    const path = newPath.trim();
    const target = newTarget.trim();
    if (!path || !target) return;
    setLocal({ ...local, routes: [...local.routes, { path, target }] });
    setNewPath("");
    setNewTarget("");
  };

  const removeRoute = (idx: number) => {
    setLocal({ ...local, routes: local.routes.filter((_, i) => i !== idx) });
  };

  const updateRoute = (idx: number, field: keyof RouteConfig, value: string) => {
    const updated = [...local.routes];
    updated[idx] = { ...updated[idx], [field]: value };
    setLocal({ ...local, routes: updated });
  };

  const inputCls =
    "w-full px-3 py-1.5 border border-gray-200 rounded-md text-sm focus:outline-none focus:border-black focus:ring-1 focus:ring-black disabled:bg-gray-50 transition-colors";

  return (
    <div className="space-y-5">
      <Card className="p-6">
        <CardHeader title="全局设置" status={{ enabled: local.enabled }} />

        <div className="space-y-5">
          <ToggleRow
            label="启用反向代理"
            checked={local.enabled}
            onChange={(v) => setLocal({ ...local, enabled: v })}
            disabled={saving}
          />

          <Input
            label="监听地址"
            value={local.listen}
            onChange={(v) => setLocal({ ...local, listen: v })}
            placeholder=":443"
            disabled={saving}
          />

          <ToggleRow
            label="启用 TLS"
            checked={local.tls}
            onChange={(v) => setLocal({ ...local, tls: v })}
            disabled={saving}
          />

          {local.tls && (
            <>
              <Input
                label="证书路径"
                value={local.cert}
                onChange={(v) => setLocal({ ...local, cert: v })}
                placeholder=".cache/cert.pem"
                disabled={saving}
              />
              <Input
                label="密钥路径"
                value={local.key}
                onChange={(v) => setLocal({ ...local, key: v })}
                placeholder=".cache/key.pem"
                disabled={saving}
              />
            </>
          )}
        </div>
      </Card>

      <Card>
        <div className="px-6 py-4 border-b border-gray-100">
          <h2 className="text-lg font-semibold text-black">代理规则</h2>
        </div>

        <table className="w-full text-left">
          <thead>
            <tr className="bg-gray-50 text-xs text-gray-500 uppercase tracking-wider">
              <th className="px-6 py-2.5 font-medium">源路径</th>
              <th className="px-6 py-2.5 font-medium">目标地址</th>
              <th className="px-6 py-2.5 font-medium text-right">操作</th>
            </tr>
          </thead>
          <tbody className="divide-y divide-gray-100">
            {local.routes.length === 0 && (
              <tr>
                <td colSpan={3} className="px-6 py-8 text-center text-sm text-gray-400">
                  暂无代理规则，点击下方添加
                </td>
              </tr>
            )}
            {local.routes.map((route, idx) => (
              <tr key={idx} className="hover:bg-gray-50/50 transition-colors">
                <td className="px-6 py-2.5">
                  <input
                    type="text"
                    value={route.path}
                    onChange={(e) => updateRoute(idx, "path", e.target.value)}
                    disabled={saving}
                    placeholder="/api/"
                    className={inputCls}
                  />
                </td>
                <td className="px-6 py-2.5">
                  <input
                    type="text"
                    value={route.target}
                    onChange={(e) => updateRoute(idx, "target", e.target.value)}
                    disabled={saving}
                    placeholder="http://127.0.0.1:3000"
                    className={inputCls}
                  />
                </td>
                <td className="px-6 py-2.5 text-right">
                  <button
                    onClick={() => removeRoute(idx)}
                    disabled={saving}
                    className="text-gray-400 hover:text-black transition-colors disabled:opacity-30"
                  >
                    <Trash2 size={16} />
                  </button>
                </td>
              </tr>
            ))}
          </tbody>
        </table>

        <div className="px-6 py-3 border-t border-gray-100 bg-gray-50/50 flex gap-3 items-end">
          <div className="flex-1">
            <label className="block text-xs text-gray-400 mb-1">源路径</label>
            <input
              type="text"
              value={newPath}
              onChange={(e) => setNewPath(e.target.value)}
              disabled={saving}
              placeholder="/api/"
              className={inputCls}
            />
          </div>
          <div className="flex-1">
            <label className="block text-xs text-gray-400 mb-1">目标地址</label>
            <input
              type="text"
              value={newTarget}
              onChange={(e) => setNewTarget(e.target.value)}
              disabled={saving}
              placeholder="http://127.0.0.1:3000"
              className={inputCls}
            />
          </div>
          <button
            onClick={addRoute}
            disabled={saving || !newPath.trim() || !newTarget.trim()}
            className="inline-flex items-center px-3.5 py-1.5 bg-black text-white text-sm font-medium rounded-md hover:bg-gray-800 disabled:opacity-40 disabled:cursor-not-allowed transition-colors whitespace-nowrap"
          >
            <Plus size={14} className="mr-1.5" /> 添加
          </button>
        </div>

        <div className="px-6 py-3 border-t border-gray-100 flex justify-end">
          <SaveButton saving={saving} onClick={() => onSave(local)} />
        </div>
      </Card>
    </div>
  );
};

export default ReverseProxy;
