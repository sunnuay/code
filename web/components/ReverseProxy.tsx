import { useState, useEffect } from "react";
import { Plus, Trash2, RefreshCw } from "lucide-react";
import type { ReverseConfig, RouteConfig } from "../App";

interface Props {
	config: ReverseConfig;
	onSave: (c: ReverseConfig) => void;
	saving: boolean;
}

const ReverseProxy = ({ config, onSave, saving }: Props) => {
	const [local, setLocal] = useState<ReverseConfig>(config);
	const [newPath, setNewPath] = useState("");
	const [newTarget, setNewTarget] = useState("");

	useEffect(() => {
		setLocal(config);
	}, [config]);

	const addRoute = () => {
		const path = newPath.trim();
		const target = newTarget.trim();
		if (!path || !target) return;
		setLocal({
			...local,
			routes: [...local.routes, { path, target }],
		});
		setNewPath("");
		setNewTarget("");
	};

	const removeRoute = (idx: number) => {
		setLocal({
			...local,
			routes: local.routes.filter((_, i) => i !== idx),
		});
	};

	const updateRoute = (
		idx: number,
		field: keyof RouteConfig,
		value: string,
	) => {
		const updated = [...local.routes];
		updated[idx] = { ...updated[idx], [field]: value };
		setLocal({ ...local, routes: updated });
	};

	return (
		<div className="space-y-6">
			{/* global settings card */}
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
					<div className="flex items-center gap-3">
						<label className="text-sm font-medium text-gray-700">
							启用反向代理
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
							监听地址
						</label>
						<input
							type="text"
							value={local.listen}
							onChange={(e) => setLocal({ ...local, listen: e.target.value })}
							disabled={saving}
							placeholder=":443"
							className="w-full px-4 py-2 border border-gray-200 rounded-lg focus:ring-2 focus:ring-blue-500 focus:border-transparent outline-none disabled:bg-gray-50"
						/>
					</div>
				</div>
			</div>

			{/* routes card */}
			<div className="bg-white rounded-xl border border-gray-100 shadow-sm overflow-hidden">
				<div className="p-6 border-b border-gray-100">
					<h2 className="text-lg font-semibold text-gray-800">代理规则</h2>
				</div>

				<table className="w-full text-left border-collapse">
					<thead>
						<tr className="bg-gray-50 text-gray-500 text-sm">
							<th className="px-6 py-3 font-medium">源路径</th>
							<th className="px-6 py-3 font-medium">目标地址</th>
							<th className="px-6 py-3 font-medium text-right">操作</th>
						</tr>
					</thead>
					<tbody className="divide-y divide-gray-100">
						{local.routes.length === 0 && (
							<tr>
								<td
									colSpan={3}
									className="px-6 py-8 text-center text-gray-400"
								>
									暂无代理规则，点击下方添加
								</td>
							</tr>
						)}
						{local.routes.map((route, idx) => (
							<tr key={idx} className="hover:bg-gray-50">
								<td className="px-6 py-3">
									<input
										type="text"
										value={route.path}
										onChange={(e) => updateRoute(idx, "path", e.target.value)}
										disabled={saving}
										placeholder="/api/"
										className="w-full px-3 py-1.5 border border-gray-200 rounded-lg text-sm focus:ring-2 focus:ring-blue-500 outline-none disabled:bg-gray-50"
									/>
								</td>
								<td className="px-6 py-3">
									<input
										type="text"
										value={route.target}
										onChange={(e) =>
											updateRoute(idx, "target", e.target.value)
										}
										disabled={saving}
										placeholder="http://127.0.0.1:3000"
										className="w-full px-3 py-1.5 border border-gray-200 rounded-lg text-sm focus:ring-2 focus:ring-blue-500 outline-none disabled:bg-gray-50"
									/>
								</td>
								<td className="px-6 py-3 text-right">
									<button
										onClick={() => removeRoute(idx)}
										disabled={saving}
										className="text-red-500 hover:text-red-700 transition-colors disabled:opacity-40"
									>
										<Trash2 size={18} />
									</button>
								</td>
							</tr>
						))}
					</tbody>
				</table>

				{/* add new route */}
				<div className="p-4 border-t border-gray-100 bg-gray-50 flex gap-3 items-end">
					<div className="flex-1">
						<label className="block text-xs text-gray-500 mb-1">源路径</label>
						<input
							type="text"
							value={newPath}
							onChange={(e) => setNewPath(e.target.value)}
							disabled={saving}
							placeholder="/api/"
							className="w-full px-3 py-1.5 border border-gray-200 rounded-lg text-sm focus:ring-2 focus:ring-blue-500 outline-none disabled:bg-gray-50"
						/>
					</div>
					<div className="flex-1">
						<label className="block text-xs text-gray-500 mb-1">目标地址</label>
						<input
							type="text"
							value={newTarget}
							onChange={(e) => setNewTarget(e.target.value)}
							disabled={saving}
							placeholder="http://127.0.0.1:3000"
							className="w-full px-3 py-1.5 border border-gray-200 rounded-lg text-sm focus:ring-2 focus:ring-blue-500 outline-none disabled:bg-gray-50"
						/>
					</div>
					<button
						onClick={addRoute}
						disabled={saving || !newPath.trim() || !newTarget.trim()}
						className="flex items-center px-4 py-1.5 bg-blue-600 text-white hover:bg-blue-700 rounded-lg transition-colors disabled:opacity-50 whitespace-nowrap"
					>
						<Plus size={16} className="mr-1.5" /> 添加
					</button>
				</div>

				{/* save */}
				<div className="p-4 border-t border-gray-100 flex justify-end">
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

export default ReverseProxy;
