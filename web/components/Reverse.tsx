import { useState } from "react";
import type { ReverseConfig, RouteConfig } from "./Types";
import { useConfigSection, SectionWithToggle, ToggleRow, Input } from "./UI";

interface Props {
  config: ReverseConfig;
  onChange: (c: ReverseConfig) => void;
}

const tdCls =
  `w-full px-2.5 py-1.5 bg-ctp-base border border-ctp-surface0 rounded-md ` +
  `text-xs text-ctp-text font-mono placeholder:text-ctp-overlay1 ` +
  `focus:outline-none focus:border-ctp-pink focus:ring-2 focus:ring-ctp-pink/15 transition-colors`;

export const Reverse = ({ config, onChange }: Props) => {
  const [local, update] = useConfigSection(config, onChange);
  const [newPath, setNewPath] = useState("");
  const [newTarget, setNewTarget] = useState("");

  const addRoute = () => {
    const path = newPath.trim(),
      target = newTarget.trim();
    if (!path || !target) return;
    update({ routes: [...local.routes, { path, target }] });
    setNewPath("");
    setNewTarget("");
  };

  const enterAdd = (e: React.KeyboardEvent) => {
    if (e.key === "Enter") addRoute();
  };

  const removeRoute = (i: number) =>
    update({ routes: local.routes.filter((_, j) => j !== i) });
  const updateRoute = (i: number, f: keyof RouteConfig, v: string) => {
    const next = [...local.routes];
    next[i] = { ...next[i], [f]: v };
    update({ routes: next });
  };

  return (
    <div className="space-y-5">
      <SectionWithToggle
        title="Reverse Proxy"
        enabled={local.enabled}
        onToggle={(v) => update({ enabled: v })}
      />

      <Input
        mono
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
        <div className="border-ctp-surface0 grid grid-cols-2 gap-3 border-l-2 pl-4">
          <Input
            mono
            label="Cert Path"
            value={local.cert}
            onChange={(v) => update({ cert: v })}
            placeholder=".cache/cert.pem"
          />
          <Input
            mono
            label="Key Path"
            value={local.key}
            onChange={(v) => update({ key: v })}
            placeholder=".cache/key.pem"
          />
        </div>
      )}

      <div>
        <h3 className="text-ctp-subtext0 mb-3 text-sm font-medium">
          Proxy Rules
        </h3>
        <div className="border-ctp-surface0 overflow-hidden rounded-lg border">
          <table className="w-full text-left">
            <thead>
              <tr className="bg-ctp-crust text-ctp-overlay1 text-xs">
                <th className="px-3 py-2 font-medium">Source Path</th>
                <th className="w-6 px-1 py-2" />
                <th className="px-3 py-2 font-medium">Target</th>
                <th className="w-10 px-3 py-2 font-medium" />
              </tr>
            </thead>
            <tbody className="divide-ctp-surface0 divide-y">
              {local.routes.length === 0 ? (
                <tr>
                  <td
                    colSpan={4}
                    className="text-ctp-overlay1 px-3 py-8 text-center text-sm"
                  >
                    No proxy rules — add one below
                  </td>
                </tr>
              ) : (
                local.routes.map((route, i) => (
                  <tr
                    key={i}
                    className="group hover:bg-ctp-surface0/60 transition-colors"
                  >
                    <td className="px-3 py-1.5">
                      <input
                        type="text"
                        value={route.path}
                        onChange={(e) => updateRoute(i, "path", e.target.value)}
                        placeholder="/api/"
                        className={tdCls}
                      />
                    </td>
                    <td className="text-ctp-overlay1 px-1 py-1.5 text-center text-xs select-none">
                      &rarr;
                    </td>
                    <td className="px-3 py-1.5">
                      <input
                        type="text"
                        value={route.target}
                        onChange={(e) =>
                          updateRoute(i, "target", e.target.value)
                        }
                        placeholder=""
                        className={tdCls}
                      />
                    </td>
                    <td className="px-3 py-1.5 text-center">
                      <button
                        onClick={() => removeRoute(i)}
                        className="text-ctp-overlay1 hover:text-ctp-red text-sm leading-none transition-colors"
                      >
                        &times;
                      </button>
                    </td>
                  </tr>
                ))
              )}
            </tbody>
          </table>

          <div className="border-ctp-surface0 bg-ctp-crust/60 flex items-end gap-2 border-t px-3 py-2">
            <input
              type="text"
              value={newPath}
              onChange={(e) => setNewPath(e.target.value)}
              placeholder="Path — /api/"
              className={`${tdCls} flex-1`}
              onKeyDown={enterAdd}
            />
            <input
              type="text"
              value={newTarget}
              onChange={(e) => setNewTarget(e.target.value)}
              placeholder="Target — http://..."
              className={`${tdCls} flex-1`}
              onKeyDown={enterAdd}
            />
            <button
              onClick={addRoute}
              disabled={!newPath.trim() || !newTarget.trim()}
              className="bg-ctp-pink hover:bg-ctp-pink/85 text-ctp-base rounded-full px-2.5 py-1.5 text-xs font-medium whitespace-nowrap transition-colors disabled:cursor-not-allowed disabled:opacity-30"
            >
              + Add
            </button>
          </div>
        </div>
      </div>
    </div>
  );
};
