import { useState, useEffect } from "react";
import { RefreshCw } from "lucide-react";
import type { ForwardConfig } from "../App";

interface Props {
	config: ForwardConfig;
	onSave: (c: ForwardConfig) => void;
	saving: boolean;
}

const ForwardProxy = ({ config, onSave, saving }: Props) => {
	const [local, setLocal] = useState<ForwardConfig>(config);

	useEffect(() => {
		setLocal(config);
	}, [config]);

	return (
		<div className="space-y-6">
			<div className="bg-white p-6 rounded-xl border border-gray-100 shadow-sm">
				<div className="flex justify-between items-center mb-6">
					<h2 className="text-lg font-semibold text-gray-800">全局设置</h2>
					<span
						className={`px-3 py-1 text-sm rounded-full flex items-center ${
							local.enabled
								? "bg-green-100 text-green-700"
								: "bg-gray-100 text-gray-500"
						}`}
					>
						<span
							className={`w-2 h-2 rounded-full mr-2 ${
								local.enabled ? "bg-green-500" : "bg-gray-400"
							}`}
						/>
						{local.enabled ? "已启用" : "已停用"}
					</span>
				</div>

				<div className="space-y-5">
					{/* enable toggle */}
					<div className="flex items-center gap-3">
						<label className="text-sm font-medium text-gray-700">
							启用正向代理
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

					{/* listen */}
					<div>
						<label className="block text-sm font-medium text-gray-700 mb-2">
							监听地址
						</label>
						<input
							type="text"
							value={local.listen}
							onChange={(e) => setLocal({ ...local, listen: e.target.value })}
							disabled={saving}
							placeholder=":10001"
							className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none disabled:bg-gray-50"
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
		</div>
	);
};

export default ForwardProxy;
