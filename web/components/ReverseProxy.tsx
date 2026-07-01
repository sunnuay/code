import { useState, useEffect } from "react";
import type { ReverseConfig, RouteConfig } from "../App";
import { SectionHeader, ToggleRow, MonoInput } from "./Primitives";

interface Props {
  config: ReverseConfig;
  onChange: (c: ReverseConfig) => void;
}

const tdInputCls =
  "w-full px-2.5 py-1.5 bg-ctp-base border border-ctp-surface0 rounded-md " +
  "text-xs text-ctp-text font-mono placeholder:text-ctp-overlay1 " +
  "focus:outline-none focus:border-ctp-pink focus:ring-2 focus:ring-ctp-pink/15 " +
  "transition-colors duration-150";

const ReverseProxy = ({ config, onChange }: Props) => {
  const [local, setLocal] = useState<ReverseConfig>(config);
  const [newPath, setNewPath] = useState("");
  const [newTarget, setNewTarget] = useState("");

  useEffect(() => {
    setLocal(config);
  }, [config]);

  const update = (patch: Partial<ReverseConfig>) => {
    const next = { ...local, ...patch };
    setLocal(next);
    onChange(next);
  };

  const addRoute = () => {
    const path = newPath.trim();
    const target = newTarget.trim();
    if (!path || !target) return;
    update({ routes: [...local.routes, { path, target }] });
    setNewPath("");
    setNewTarget("");
  };

  const removeRoute = (idx: number) => {
    update({ routes: local.routes.filter((_, i) => i !== idx) });
  };

  const updateRoute = (
    idx: number,
    field: keyof RouteConfig,
    value: string,
  ) => {
    const updated = [...local.routes];
    updated[idx] = { ...updated[idx], [field]: value };
    update({ routes: updated });
  };

  return (
    <div className="space-y-5">
      <div className="flex items-center justify-between">
        <SectionHeader title="Reverse Proxy" />
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
        placeholder=":443"
      />

      <ToggleRow
        label="TLS"
        checked={local.tls}
        onChange={(v) => update({ tls: v })}
      />

      {local.tls && (
        <div className="grid grid-cols-2 gap-3 pl-4 border-l-2 border-ctp-surface0">
          <MonoInput
            label="Cert Path"
            value={local.cert}
            onChange={(v) => update({ cert: v })}
            placeholder=".cache/cert.pem"
          />
          <MonoInput
            label="Key Path"
            value={local.key}
            onChange={(v) => update({ key: v })}
            placeholder=".cache/key.pem"
          />
        </div>
      )}

      {/* Route table */}
      <div>
        <h3 className="text-sm font-medium text-ctp-subtext0 mb-3">
          Proxy Rules
        </h3>

        <div className="border border-ctp-surface0 rounded-lg overflow-hidden">
          <table className="w-full text-left">
            <thead>
              <tr className="bg-ctp-crust text-xs text-ctp-overlay1">
                <th className="px-3 py-2 font-medium">Source Path</th>
                <th className="px-1 py-2 w-6" />
                <th className="px-3 py-2 font-medium">Target</th>
                <th className="px-3 py-2 font-medium w-10" />
              </tr>
            </thead>
            <tbody className="divide-y divide-ctp-surface0">
              {local.routes.length === 0 && (
                <tr>
                  <td
                    colSpan={4}
                    className="px-3 py-8 text-center text-sm text-ctp-overlay1"
                  >
                    No proxy rules — add one below
                  </td>
                </tr>
              )}
              {local.routes.map((route, idx) => (
                <tr key={idx} className="group hover:bg-ctp-surface0/60 transition-colors">
                  <td className="px-3 py-1.5">
                    <input
                      type="text"
                      value={route.path}
                      onChange={(e) => updateRoute(idx, "path", e.target.value)}
                      placeholder="/api/"
                      className={tdInputCls}
                    />
                  </td>
                  <td className="px-1 py-1.5 text-center text-xs text-ctp-overlay1 select-none">
                    &rarr;
                  </td>
                  <td className="px-3 py-1.5">
                    <input
                      type="text"
                      value={route.target}
                      onChange={(e) => updateRoute(idx, "target", e.target.value)}
                      placeholder="http://127.0.0.1:3000"
                      className={tdInputCls}
                    />
                  </td>
                  <td className="px-3 py-1.5 text-center">
                    <button
                      onClick={() => removeRoute(idx)}
                      className="text-ctp-overlay1 hover:text-ctp-red transition-colors text-sm leading-none"
                      title="Remove"
                    >
                      &times;
                    </button>
                  </td>
                </tr>
              ))}
            </tbody>
          </table>

          {/* Add route form */}
          <div className="px-3 py-2 border-t border-ctp-surface0 bg-ctp-crust/60 flex gap-2 items-end">
            <div className="flex-1">
              <input
                type="text"
                value={newPath}
                onChange={(e) => setNewPath(e.target.value)}
                placeholder="Path — /api/"
                className={tdInputCls}
                onKeyDown={(e) => {
                  if (e.key === "Enter") addRoute();
                }}
              />
            </div>
            <div className="flex-1">
              <input
                type="text"
                value={newTarget}
                onChange={(e) => setNewTarget(e.target.value)}
                placeholder="Target — http://..."
                className={tdInputCls}
                onKeyDown={(e) => {
                  if (e.key === "Enter") addRoute();
                }}
              />
            </div>
            <button
              onClick={addRoute}
              disabled={!newPath.trim() || !newTarget.trim()}
              className="px-2.5 py-1.5 bg-ctp-pink hover:bg-ctp-pink/85 text-ctp-base text-xs font-medium rounded-lg
                disabled:opacity-30 disabled:cursor-not-allowed transition-colors whitespace-nowrap"
            >
              + Add
            </button>
          </div>
        </div>
      </div>
    </div>
  );
};

export default ReverseProxy;
