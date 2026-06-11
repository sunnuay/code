import { useState, useEffect } from "react";
import { RefreshCw } from "lucide-react";
import type { DDNSConfig } from "../App";

interface Props {
	config: DDNSConfig;
	onSave: (c: DDNSConfig) => void;
	saving: boolean;
}

const DDNS = ({ config, onSave, saving }: Props) => {
	const [local, setLocal] = useState<DDNSConfig>(config);

	useEffect(() => {
		setLocal(config);
	}, [config]);

	return (
		<div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm max-w-2xl">
			<h2 className="text-lg font-semibold text-gray-800 mb-6">域名配置</h2>

			<div className="space-y-5">
				{/* enable toggle */}
				<div className="flex items-center gap-3">
					<label className="text-sm font-medium text-gray-700">
						启用 DDNS
					</label>
					<button
						type="button"
						role="switch"
						aria-checked={local.enabled}
						onClick={() => setLocal({ ...local, enabled: !local.enabled })}
						disabled={saving}
						className={`relative inline-flex h-6 w-11 items-center rounded-full transition-colors focus:outline-none focus:ring-2 focus:ring-blue-300 disabled:opacity-50 ${
							local.enabled ? "bg-blue-600" : "bg-gray-300"
						}`}
					>
						<span
							className={`inline-block h-4 w-4 transform rounded-full bg-white transition-transform ${
								local.enabled ? "translate-x-6" : "translate-x-1"
							}`}
						/>
					</button>
				</div>

				<div>
					<label className="block text-sm font-medium text-gray-700 mb-2">
						域名
					</label>
					<input
						type="text"
						value={local.domain}
						onChange={(e) => setLocal({ ...local, domain: e.target.value })}
						disabled={saving}
						placeholder="example.com"
						className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none disabled:bg-gray-50"
					/>
				</div>

				<div>
					<label className="block text-sm font-medium text-gray-700 mb-2">
						API Token
					</label>
					<input
						type="password"
						value={local.api_token}
						onChange={(e) =>
							setLocal({ ...local, api_token: e.target.value })
						}
						disabled={saving}
						placeholder="Cloudflare API Token"
						className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none disabled:bg-gray-50"
					/>
				</div>

				<div>
					<label className="block text-sm font-medium text-gray-700 mb-2">
						同步间隔 (秒)
					</label>
					<input
						type="number"
						value={local.interval}
						onChange={(e) =>
							setLocal({ ...local, interval: parseInt(e.target.value) || 0 })
						}
						disabled={saving}
						min={10}
						className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 outline-none disabled:bg-gray-50"
					/>
				</div>

				<div className="pt-2 flex justify-end">
					<button
						onClick={() => onSave(local)}
						disabled={saving}
						className="flex items-center px-4 py-2 bg-blue-600 text-white hover:bg-blue-700 rounded-lg transition-colors disabled:opacity-50"
					>
						<RefreshCw
							size={16}
							className={`mr-2 ${saving ? "animate-spin" : ""}`}
						/>
						{saving ? "保存中..." : "保存配置"}
					</button>
				</div>
			</div>
		</div>
	);
};

export default DDNS;
